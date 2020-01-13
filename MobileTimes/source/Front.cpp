#include "Front.h"

using ut::Front;

Front::Front()
{}
Front::~Front()
{}

void Front::clear_self()
{
	mRenders.clear();
	mTypeToSprite.clear();
}
ut::ExitCode Front::init_self(const ut::GameState& dcGameState)
{
	clear_self();
	auto result = ut::ExitCode::okay;
	const auto cSpriteTypeToFileName =
		m_gameState_to_spriteTypeToFileName(dcGameState);
	for (const auto& cKeyValue : cSpriteTypeToFileName)
	{
		const ut::SpriteType& cSpriteType = cKeyValue.first;
		const std::string& cFileName = cKeyValue.second;
		mTypeToSprite[cSpriteType] = ut::Sprite();
		ut::Sprite& sprite = mTypeToSprite[cSpriteType];
		result = sprite.init_self(cFileName);
	}
	return result;
}
void Front::draw_self(sf::RenderWindow& window)
{
	for (const auto& cRender : mRenders)
	{
		// HACK TODO check SpriteType during initing Scenario;
		const bool cIsSpriteTypeCorrect =
			mTypeToSprite.find(cRender.spriteType) != mTypeToSprite.end();
		if (!cIsSpriteTypeCorrect)
		{
			return;
		}
		ut::Sprite& sprite = mTypeToSprite[cRender.spriteType];
		sprite.set_render(cRender);
		window.draw(sprite);
	}
}

std::map<ut::SpriteType, std::string>
Front::m_gameState_to_spriteTypeToFileName(const ut::GameState& dcGameState)
{
	std::map<SpriteType, std::string> spriteTypeToFileName;
	spriteTypeToFileName[ut::SpriteType::error] = "error";
	spriteTypeToFileName[ut::SpriteType::none] = "none";
	switch (dcGameState)
	{
	case ut::GameState::menu:
		spriteTypeToFileName[ut::SpriteType::buttonGreen] = "buttonGreen";
		break;
	case ut::GameState::ingame:
		spriteTypeToFileName[ut::SpriteType::squadKnight] = "squadKnight";
		break;
	default:
		assert(false);
	}
	for (auto& keyValue : spriteTypeToFileName)
	{
		const std::string cSpriteFolder = "sprites";
		std::string& fileName = keyValue.second;
		fileName = cSpriteFolder + '/' + fileName + ".png";
	}
	return spriteTypeToFileName;
}