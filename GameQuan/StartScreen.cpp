#include "stdafx.h"
#include <SDL_image.h>

#include "StartScreen.h"

extern bool gQuit;

StartScreen::StartScreen(StateManager* stateManager) : GameScreen(stateManager), frame(0), animationTime(0.0f)
{
    createGUI();
	pigTexture = AssetManager::getInstance()->getTexture("pig.png");
	// Load pig animation frames
	for (int i = 0; i < PIG_ANIMATION_FRAMES; ++i)
	{
		animationClips[i].x = i * PIG_WIDTH;
		animationClips[i].y = 0;
		animationClips[i].w = PIG_WIDTH;
		animationClips[i].h = PIG_HEIGHT;
	}
}

StartScreen::~StartScreen()
{
	for (auto& component : GUIComponents)
	{
		delete component;
	}
	GUIComponents.clear();
	SDL_DestroyTexture(pigTexture);
}

void StartScreen::renderScreen()
{
    //render Background
    SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("start_screen_background.png"), NULL, NULL);
	// render buttons
	renderWidget();
	// render pig
	SDL_Rect srcRect = animationClips[frame];
	SDL_Rect destRect = { SCREEN_WIDTH / 2 - PIG_WIDTH / 2, 50, 100, 100 };
	SDL_RenderCopy(gWindow->getRenderer(), pigTexture, &srcRect, &destRect);
	
}

void StartScreen::updateScreen(float deltaTime)
{
	animationTime += deltaTime;
	if (animationTime >= PIG_ANIMATION_SPEED) 
	{
		frame = (frame + 1) % PIG_ANIMATION_FRAMES;
		//std::cout << frame << std::endl;
		animationTime = 0.0f;
	}
}

void StartScreen::handleEvent(const SDL_Event& event)
{
    for (auto& component : GUIComponents)
    {
        component->handleEvent(event);
    }
}

void StartScreen::createGUI()
{
    createButton("button_pvp.png", { 555, 400 }, std::bind(&StartScreen::startPVPGame, this));
    createButton("button_exit.png", { 555, 480 }, []() { gQuit = true; });
	createButton("button_pve.png", { 555, 320 }, std::bind(&StartScreen::startPVEGame, this));
    createButton("button_about.png", {555, 560}, std::bind(&StartScreen::gotoAboutScreen,this));
}

void StartScreen::startPVPGame()
{
    stateManager->switchScreen(StateManager::Screen::SettingScreen);
}

void StartScreen::startPVEGame()
{
	stateManager->switchScreen(StateManager::Screen::PveSettingScreen);
}

void StartScreen::gotoAboutScreen()
{
    stateManager->switchScreen(StateManager::Screen::AboutScreen);
}


void StartScreen::exitGame()
{
    //stateManager->exitGame();
    std::cout << "Exiting game..." << std::endl;
}
