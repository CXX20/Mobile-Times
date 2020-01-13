#ifndef UTHEADER_TERRAIN
#define UTHEADER_TERRAIN
#include <vector>
#include <set>
#include <SFML\System\Vector2.hpp>
#include "globals.h"
#include "SpriteType.h"

namespace ut {
class Terrain
{
public:
	struct Tile
	{
		Tile(const sf::Vector2<size_t>& dcPosition = sf::Vector2<size_t>(0, 0),
			const SpriteType& dcSpriteType = SpriteType::error,
			const int& dcSquadId = glb::NegativeId::scNone)
		{
			position = dcPosition;
			spriteType = dcSpriteType;
			activeSquadId = dcSquadId;
		}
		virtual ~Tile()
		{}

		sf::Vector2<size_t> position;
		// TODO spriteTypeTwo (trees etc);
		SpriteType spriteType;
		int activeSquadId;
		std::set<int> inactiveSquadsIds;
	};

	Terrain();
	virtual ~Terrain();

	const auto& get_size() const
	{
		return mSize;
	}
	const Tile& get_tile(const size_t& dcX, const size_t& dcY) const
	{
		return mTiles[dcY][dcX];
	}

	ExitCode set_tile(const size_t&, const size_t&, const Tile&);

	ExitCode init_self(const size_t&, const size_t&);

private:
	sf::Vector2<size_t> mSize;
	// mTiles[y][x] == Tile at (x, y);
	std::vector<std::vector<Tile>> mTiles;
};
} // namespace ut;

#endif // ! UTHEADER_TERRAIN;
