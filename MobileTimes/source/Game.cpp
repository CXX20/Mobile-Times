#include "Game.h"

using ut::Game;

const std::pair<int, int> Game::scVersion(0, 0);

Game::Game()
{
	mState = ut::GameState::error;
	mWindow.create(sf::VideoMode::getDesktopMode(),
		"Uneasy Time", sf::Style::Fullscreen);
	init_self(ut::GameState::menu);
}
Game::~Game()
{}

void Game::init_self(const ut::GameState& dcGameState)
{
	const ut::ExitCode cExitCodeBack = mBack.init_self(dcGameState);
	const ut::ExitCode cExitCodeFront = mFront.init_self(dcGameState);
	if (cExitCodeBack  == ut::ExitCode::okay &&
		cExitCodeFront == ut::ExitCode::okay)
	{
		mState = dcGameState;
	} else {
		mState = ut::GameState::error;
#if !IS_UTRELEASE
		std::cout << "Initialization failed." << std::endl;
#endif // ! IS_UTRELEASE;
	}
}

void Game::handle_event()
{
	if (!mEvent.type == sf::Event::Closed &&
		!(mEvent.type == sf::Event::KeyPressed &&
		mEvent.key.code == sf::Keyboard::Escape))
	{
		ut::ExitCode result = mBack.handle_event(mEvent);
		if (result == ut::ExitCode::changeGameState)
		{
			const auto dcGameState = mBack.get_dGameState();
			init_self(dcGameState);
		}
	} else {
		mWindow.close();
	}
}

void Game::update_self()
{}

void Game::draw_self()
{
	const auto cRenders = mBack.compute_renders();
	mFront.set_renders(cRenders);
	mWindow.clear(sf::Color::Black);
	mFront.draw_self(mWindow);
	mWindow.display();
}