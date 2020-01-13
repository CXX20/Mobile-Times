#ifndef UTHEADER_GLOBALS
#define UTHEADER_GLOBALS
#if IS_UTRELEASE
#define NDEBUG
#endif // IS_UTRELEASE;
#include <iostream>
#include <cassert>
#include <SFML\Window\VideoMode.hpp>
#include <SFML\System\Vector2.hpp>
#include "ExitCode.h"

#define MIN_IF_UNEQUAL_ELSE_FIRST(a, b) \
	((b) < (a) ? (b) : (a))
#define MAX_IF_UNEQUAL_ELSE_FIRST(a, b) \
	((a) < (b) ? (b) : (a))
#define LAST_ELEMENT_OF_UNEMPTY(container) \
	(container)[(container).size() - 1]
#define IF_UNEQUAL_RETURN_IS_LESS(a, b) \
	if ((a) != (b)) \
		return (a) < (b)
#define IS_RIGHT_UNSTRICT_INEQUALITY(a, b, c) \
	((a) <= (b) && (b) <= (c))

namespace ut {
namespace glb {
struct NegativeId
{
	static const int scNone = -1;
	static const int scAny = -2;
	static const int scError = -3;
};
static const int cIdFirst = 0;
static const sf::Vector2<size_t> ncTiles(20, 10);
static const unsigned int ncPixelsPerTile = MIN_IF_UNEQUAL_ELSE_FIRST(
	sf::VideoMode::getDesktopMode().width / ncTiles.x,
	sf::VideoMode::getDesktopMode().height / ncTiles.y);
} // namespace glb;
} // namespace ut;

#endif // ! UTHEADER_GLOBALS;
