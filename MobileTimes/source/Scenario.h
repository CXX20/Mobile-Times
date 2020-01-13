#ifndef UTHEADER_SCENARIO
#define UTHEADER_SCENARIO
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "Script.h"
#include "Squad.h"
#include "Terrain.h"

namespace ut {
class Scenario
{
public:
	Scenario();
	virtual ~Scenario();

	const auto& get_idToSquad() const
	{
		return mIdToSquad;
	}
	const auto& get_terrain() const
	{
		return mTerrain;
	}

	void move_squad(const int& dcId, const sf::Vector2i& dcMovement);

	void clear_self()
	{
		mIdToSquad.clear();
		mTerrain.init_self(0, 0);
	}
	ExitCode init_self(const std::string&);

private:
	enum class MOperatorType;

	std::map<int, Squad> mIdToSquad;
	Terrain mTerrain;
	std::set<std::pair<int, int>> mBattleSquadIds;

	std::vector<std::string> m_split_string(const std::string&);
	ExitCode m_init_self_terrain_size(std::ifstream*);
	ExitCode m_init_self_terrain_tile(std::ifstream*, const size_t& cIndex);
	ExitCode m_init_self_nSquads(std::ifstream*);
	ExitCode m_init_self_squad(std::ifstream*, const int& cIndex);
};
} // namespace ut;

#endif // ! UTHEADER_SCENARIO;