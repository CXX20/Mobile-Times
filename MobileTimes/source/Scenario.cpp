#include "Scenario.h"

using ut::Scenario;

enum class Scenario::MOperatorType
{
	mapSize,
	tile
};

Scenario::Scenario()
{}
Scenario::~Scenario()
{}

ut::ExitCode Scenario::init_self(const std::string& cFileName)
{
	auto result = ut::ExitCode::okay;
	std::ifstream inputStream;
	inputStream.open(cFileName);
	if (!inputStream.is_open())
	{
		result = ut::ExitCode::noFile;
		goto Return_Result;
	}

	result = m_init_self_terrain_size(&inputStream);
	if (result != ut::ExitCode::okay)
	{
		goto Return_Result;
	}
	for (size_t u = 0; u < mTerrain.get_size().x *
		mTerrain.get_size().y; ++u)
	{
		result = m_init_self_terrain_tile(&inputStream, u);
		if (result != ut::ExitCode::okay)
		{
			goto Return_Result;
		}
	}
	result = m_init_self_nSquads(&inputStream);
	if (result != ut::ExitCode::okay)
	{
		goto Return_Result;
	}
	for (int i = ut::glb::cIdFirst; i <= ut::glb::cIdFirst +
		mIdToSquad.rbegin()->first; ++i)
	{
		result = m_init_self_squad(&inputStream, i);
		if (result != ut::ExitCode::okay)
		{
			goto Return_Result;
		}
	}
Return_Result:
	return result;
}

void Scenario::move_squad(const int& dcId, const sf::Vector2i& dcMovement)
{
	Squad& squad = mIdToSquad[dcId];
	auto dPosition = sf::Vector2i(squad.get_position());
	ut::Terrain::Tile dTileOld =
		mTerrain.get_tile(static_cast<size_t>(dPosition.x),
			static_cast<size_t>(dPosition.y));
	const auto cTerrainSize = sf::Vector2i(mTerrain.get_size());
	dPosition += dcMovement;
	dPosition.x = MIN_IF_UNEQUAL_ELSE_FIRST(dPosition.x, cTerrainSize.x-1);
	dPosition.x = MAX_IF_UNEQUAL_ELSE_FIRST(0, dPosition.x);
	dPosition.y = MIN_IF_UNEQUAL_ELSE_FIRST(dPosition.y, cTerrainSize.y-1);
	dPosition.y = MAX_IF_UNEQUAL_ELSE_FIRST(0, dPosition.y);

	ut::Terrain::Tile dTileNew =
		mTerrain.get_tile(static_cast<size_t>(dPosition.x),
			static_cast<size_t>(dPosition.y));
	const bool cIsSquadActive = squad.get_isActive();
	const bool cIsTileNewFree =
		dTileNew.activeSquadId == ut::glb::NegativeId::scNone;
	if (cIsSquadActive && cIsTileNewFree)
	{
		dTileOld.activeSquadId = ut::glb::NegativeId::scNone;
		dTileNew.activeSquadId = dcId;
		squad.set_position(sf::Vector2<size_t>(dPosition));
	// TODO check if enemies:
	} else if (cIsSquadActive && !cIsTileNewFree) {
		// TODO add BattleRequest;
	} else if (!cIsSquadActive) {
		dTileOld.inactiveSquadsIds.erase(dcId);
		dTileNew.inactiveSquadsIds.insert(dcId);
		squad.set_position(sf::Vector2<size_t>(dPosition));
	}
	mTerrain.set_tile(dTileOld.position.x, dTileOld.position.y, dTileOld);
	mTerrain.set_tile(dTileNew.position.x, dTileNew.position.y, dTileNew);
}

// private:

std::vector<std::string> Scenario::m_split_string(const std::string& cString)
{
	std::vector<std::string> result(1);
	const char cSplitter = ' ';
	for (const auto& cChar : cString)
	{
		if (cChar != cSplitter)
		{
			LAST_ELEMENT_OF_UNEMPTY(result).push_back(cChar);
		} else if (LAST_ELEMENT_OF_UNEMPTY(result).size() != 0) {
			result.push_back(std::string());
		}
	}
	return result;
}

ut::ExitCode Scenario::m_init_self_terrain_size(std::ifstream* pInputStream)
{
	auto result = ut::ExitCode::okay;
	assert(pInputStream != nullptr);
	auto& inputStream = *pInputStream;
	try
	{
		std::string line;
		std::getline(inputStream, line);
		const auto cLineSplit = m_split_string(line);
		const int dcX = std::stoi(cLineSplit.at(0));
		const int dcY = std::stoi(cLineSplit.at(1));

		if (dcX > 0 && dcY > 0)
		{
			mTerrain.init_self(static_cast<size_t>(dcX),
				static_cast<size_t>(dcY));
		} else {
			result = ut::ExitCode::badInput;
		}
	} catch (...) {
		result = ut::ExitCode::badInput;
	}
	return result;
}
ut::ExitCode Scenario::m_init_self_terrain_tile(std::ifstream* pInputStream,
	const size_t& cIndex)
{
	auto result = ut::ExitCode::okay;
	assert(pInputStream != nullptr);
	auto& inputStream = *pInputStream;
	// KEEP_UPDATED Tile params:
	try
	{
		std::string line;
		std::getline(inputStream, line);
		const auto cLineSplit = m_split_string(line);
		const int idcSpriteType = std::stoi(cLineSplit.at(0));

		// KEEP_UPDATED SpriteType first and last:
		const auto icSpriteTypeFirst =
			static_cast<int>(ut::SpriteType::error);
		const auto icSpriteTypeLast =
			static_cast<int>(ut::SpriteType::squadKnight);
		if (IS_RIGHT_UNSTRICT_INEQUALITY(icSpriteTypeFirst,
			idcSpriteType, icSpriteTypeLast))
		{
			// KEEP_UPDATED Terrain::Tile attributes:
			ut::Terrain::Tile tile(sf::Vector2<size_t>(),
				static_cast<ut::SpriteType>(idcSpriteType));
			// .x and .x, no .y:
			result = mTerrain.set_tile(cIndex%mTerrain.get_size().x,
				cIndex/mTerrain.get_size().x, tile);
		} else {
			// ATTENTION discards set_tile()'s result;
			result = ut::ExitCode::badInput;
		}
	} catch (...) {
		result = ut::ExitCode::badInput;
	}
	return result;
}
ut::ExitCode Scenario::m_init_self_nSquads(std::ifstream* pInputStream)
{
	auto result = ut::ExitCode::okay;
	assert(pInputStream != nullptr);
	auto& inputStream = *pInputStream;
	try
	{
		std::string line;
		std::getline(inputStream, line);
		const auto cLineSplit = m_split_string(line);
		const int ndcUnits = std::stoi(cLineSplit.at(0));

		if (ndcUnits < 0)
		{
			result = ut::ExitCode::badInput;
		}
		for (int i = ut::glb::cIdFirst; i < ut::glb::cIdFirst + ndcUnits; ++i)
		{
			mIdToSquad[i] = ut::Squad();
		}
	} catch (...) {
		result = ut::ExitCode::badInput;
	}
	return result;
}
ut::ExitCode Scenario::m_init_self_squad(std::ifstream* pInputStream,
	const int& cIndex)
{
	auto result = ut::ExitCode::okay;
	assert(pInputStream != nullptr);
	auto& inputStream = *pInputStream;
	try
	{
		std::string line;
		std::getline(inputStream, line);
		const auto cLineSplit = m_split_string(line);
		// KEEP_UPDATED Squad's attributes:
		const int idcSpriteType = std::stoi(cLineSplit.at(0));
		const int dcPositionX = std::stoi(cLineSplit.at(1));
		const int dcPositionY = std::stoi(cLineSplit.at(2));
		const bool dcIsActive = std::stoi(cLineSplit.at(3));
		const int dcMoney = std::stoi(cLineSplit.at(4));

		// KEEP_UPDATED Squad's SpriteType:
		const bool cIsSpriteTypeValid =
			IS_RIGHT_UNSTRICT_INEQUALITY(
				static_cast<int>(ut::SpriteType::squadKnight),
				idcSpriteType,
				static_cast<int>(ut::SpriteType::squadKnight));
		const bool cIsPositionXValid =
			IS_RIGHT_UNSTRICT_INEQUALITY(0,
				static_cast<size_t>(dcPositionX),
				mTerrain.get_size().x-1);
		const bool cIsPositionYValid =
			IS_RIGHT_UNSTRICT_INEQUALITY(0,
				static_cast<size_t>(dcPositionY),
				mTerrain.get_size().y-1);
		const bool cIsPositionXYFree = !dcIsActive ||
			mTerrain.get_tile(static_cast<size_t>(dcPositionX),
				static_cast<size_t>(dcPositionY)).activeSquadId ==
			ut::glb::NegativeId::scNone;
		if (cIsSpriteTypeValid && cIsPositionXValid && cIsPositionYValid &&
			dcMoney >= 0 && cIsPositionXYFree)
		{
			mIdToSquad[cIndex] =
				ut::Squad(cIndex, dcIsActive,
					static_cast<ut::SpriteType>(idcSpriteType),
					sf::Vector2<size_t>(static_cast<size_t>(dcPositionX),
						static_cast<size_t>(dcPositionY)),
					dcMoney);
			ut::Terrain::Tile tile =
				mTerrain.get_tile(static_cast<size_t>(dcPositionX),
					static_cast<size_t>(dcPositionY));
			if (dcIsActive)
			{
				tile.activeSquadId = cIndex;
			} else {
				tile.inactiveSquadsIds.insert(cIndex);
			}
			mTerrain.set_tile(static_cast<size_t>(dcPositionX),
				static_cast<size_t>(dcPositionY), tile);
		} else {
			result = ut::ExitCode::badInput;
		}
	} catch (...) {
		result = ut::ExitCode::badInput;
	}
	return result;
}