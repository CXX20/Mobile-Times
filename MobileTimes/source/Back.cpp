#include "Back.h"

using ut::Back;

Back::Back()
{
	mGameState = ut::GameState::error;
}
Back::~Back()
{}

void Back::clear_self()
{
	mGameState = ut::GameState::error;
	mTypeToButton.clear();
	mScenario.clear_self();
}

ut::ExitCode Back::init_self(const ut::GameState& dcGameState)
{
	auto result = ut::ExitCode::okay;
	clear_self();
	switch (dcGameState)
	{
	case ut::GameState::menu:
		mTypeToButton[ut::Button::Type::play] =
			ut::Button(ut::Button::Type::play);
		break;
	case ut::GameState::ingame:
		// DEBUG scenario file:
		result = mScenario.init_self("maps/test.txt");
		break;
	default:
		assert(false);
		break;
	}
	if (result == ut::ExitCode::okay)
	{
		mGameState = dcGameState;
	}
	return result;
}

ut::ExitCode Back::handle_event(const sf::Event& cEvent)
{
	auto result = ut::ExitCode::okay;
	switch (cEvent.type)
	{
	case sf::Event::MouseButtonPressed:
		for (auto& keyValue : mTypeToButton)
		{
			ut::Button& button = keyValue.second;
			if (button.is_hovered(sf::Mouse::getPosition()) &&
				button.get_state() != ut::Button::State::disabled &&
				button.get_state() != ut::Button::State::unclickable)
			{
				button.set_state(ut::Button::State::holded);
			}
		}
		break;
	case sf::Event::MouseButtonReleased:
		for (auto& keyValue : mTypeToButton)
		{
			ut::Button& button = keyValue.second;
			const bool cIsHovered =
				button.is_hovered(sf::Mouse::getPosition());
			const auto& cState = button.get_state();
			if (cIsHovered && cState == ut::Button::State::holded)
			{
				result = m_press_button(&button);
			} else if (cIsHovered) {
				button.set_state(ut::Button::State::holded);
			} else if (cState == ut::Button::State::holded) {
				button.set_state(ut::Button::State::active);
			}
		}
		break;
	case sf::Event::LostFocus:
		for (auto& keyValue : mTypeToButton)
		{
			const ut::Button::Type& cType = keyValue.first;
			ut::Button& button = keyValue.second;
			if (button.get_state() != ut::Button::State::unclickable)
			{
				button.set_state(ut::Button::State::active);
			}
		}
		break;
	default:
		break;
	}
	return result;
}

std::set<ut::Render> Back::compute_renders()
{
	std::set<ut::Render> result;
	for (size_t u = 0; u < mScenario.get_terrain().get_size().x *
		mScenario.get_terrain().get_size().y; ++u)
	{
		const ut::Terrain::Tile& cTile = mScenario.get_terrain().get_tile(
			u % mScenario.get_terrain().get_size().x,
			u / mScenario.get_terrain().get_size().x);
		ut::Render render(cTile);
		result.insert(render);
	}
	for (const auto& cKeyValue : mScenario.get_idToSquad())
	{
		const ut::Squad& cSquad = cKeyValue.second;
		ut::Render render(cSquad);
		result.insert(render);
	}
	for (const auto& cKeyValue : mTypeToButton)
	{
		const ut::Button& cButton = cKeyValue.second;
		ut::Render render(cButton);
		result.insert(render);
	}
	return result;
}

// private:

ut::ExitCode Back::m_press_button(ut::Button* pButton)
{
	auto result = ut::ExitCode::okay;
	assert(pButton != nullptr);
	ut::Button& button = *pButton;
	switch (button.get_type())
	{
	case ut::Button::Type::error:
		break;
	case ut::Button::Type::play:
		result = ut::ExitCode::changeGameState;
		mdGameState = ut::GameState::ingame;
		break;
	default:
		assert(false);
		break;
	}
	button.set_state(ut::Button::State::active);
#if !IS_UTRELEASE
	if (result == ut::ExitCode::okay ||
		result == ut::ExitCode::changeGameState)
	{
		std::cout << "Button pressed." << std::endl;
	}
#endif // ! IS_UTRELEASE;
	return result;
}