#ifndef UTHEADER_BACK
#define UTHEADER_BACK
#include <map>
#include <set>
#include <SFML\Window.hpp>
#include "Button.h"
#include "ExitCode.h"
#include "GameState.h"
#include "Render.h"
#include "Scenario.h"

namespace ut {
class Back
{
public:
	Back();
	virtual ~Back();

	const auto& get_dGameState()
	{
		return mdGameState;
	}

	ExitCode init_self(const GameState&);
	void clear_self();
	ExitCode handle_event(const sf::Event&);

	std::set<Render> compute_renders();

private:
	GameState mGameState;
	GameState mdGameState;
	std::map<Button::Type, Button> mTypeToButton;
	Scenario mScenario;

	ExitCode m_press_button(Button*);
};
} // namespace ut;

#endif // ! UTHEADER_BACK;