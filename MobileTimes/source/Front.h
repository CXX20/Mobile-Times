#ifndef UTHEADER_FRONT
#define UTHEADER_FRONT
#include <map>
#include <set>
#include "GameState.h"
#include "Render.h"
#include "Sprite.h"

namespace ut {
class Front
{
public:
	Front();
	virtual ~Front();

	void set_renders(const std::set<Render>& dcRenders)
	{
		mRenders = dcRenders;
	}

	void clear_self();
	ExitCode init_self(const GameState&);
	void draw_self(sf::RenderWindow&);

private:
	std::set<Render> mRenders;
	std::map<SpriteType, Sprite> mTypeToSprite;

	std::map<SpriteType, std::string> m_gameState_to_spriteTypeToFileName(
		const GameState&);
};
} // namespace ut;

#endif // ! UTHEADER_FRONT;