#pragma once
#include <vector>

#include "GameScreen.h"
#include "Window.h"
#include "GuiComponent.h"
#include "Button.h"

extern Window* gWindow;

class StartScreen : public GameScreen
{
public:
	StartScreen(StateManager* stateManager);
	~StartScreen();
	void renderScreen();
	void updateScreen(float deltaTime);
	void handleEvent(const SDL_Event& event);

private:
	int frame;
	float animationTime;

	void createGUI();
	void startPVPGame();
	void startPVEGame();
	void gotoAboutScreen();
	void exitGame();
	SDL_Rect animationClips[PIG_ANIMATION_FRAMES];
	SDL_Texture* pigTexture;
};
