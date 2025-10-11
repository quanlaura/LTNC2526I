#pragma once

#include <functional>
#include "GameScreen.h"

extern bool gQuit;

class AboutScreen : public GameScreen
{
public:
	AboutScreen(StateManager* stateManager);
	~AboutScreen();
	void handleEvent(const SDL_Event& event);
	void renderScreen();
	void updateScreen(float deltatime);

private:
	void createGUI();
	void goToMenu();
};

