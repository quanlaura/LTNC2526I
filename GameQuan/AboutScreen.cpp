#include "stdafx.h"
#include "AboutScreen.h"

AboutScreen::AboutScreen(StateManager* stateManager) : GameScreen(stateManager)
{
    createGUI();
}

AboutScreen::~AboutScreen()
{

}


void AboutScreen::renderScreen()
{
    //load background
    SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("about_screen_background.png"), NULL, NULL);
    renderWidget();
}

void AboutScreen::updateScreen(float deltaTime)
{
        
}

void AboutScreen::handleEvent(const SDL_Event& event)
{
    handleWidgetEvent(event);
}

void AboutScreen::createGUI()
{
	SDL_Point pos;
	pos.x = 1090;
	pos.y = 10;
	createButton("button_home.png", pos, std::bind(&AboutScreen::goToMenu, this));

}

void AboutScreen::goToMenu()
{
    stateManager->switchScreen(StateManager::Screen::StartScreen);
}