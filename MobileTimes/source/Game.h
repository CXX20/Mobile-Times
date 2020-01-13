#ifndef UTHEADER_GAME
#define UTHEADER_GAME
#include "Back.h"
#include "Front.h"

namespace ut {
class Game
{
public:
	Game();
	virtual ~Game();

	// .first = major, .second = minor;
	static const std::pair<int, int> scVersion;

	bool is_opened() const
	{
		return mWindow.isOpen();
	}
	bool is_polling_event()
	{
		return mWindow.pollEvent(mEvent);
	}

	void init_self(const GameState&);

	void handle_event();
	void update_self();
	void draw_self();

private:
	sf::RenderWindow mWindow;
	sf::Event mEvent;
	GameState mState;
	Back mBack;
	Front mFront;
};
} // namespace ut;

#endif // ! UTHEADER_GAME;