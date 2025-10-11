#include "stdafx.h"
#include "EndScreen.h"

EndScreen::EndScreen(StateManager* stateManager) : GameScreen(stateManager)
{
    createGUI();
    Mix_Chunk* sound = AssetManager::getInstance()->getSoundBuffer("end_screen_sound.wav");
    if (gSoundOn) Mix_PlayChannel(-1, sound, 0);
    if (!Mix_PausedMusic())
    {
        Mix_PauseMusic();
        timePauseMusic = 6;
    }
    else
    {
        timePauseMusic = -1;
    }
}

EndScreen::~EndScreen()
{

}

void EndScreen::renderScreen()
{
    //load background
    SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("end_screen_background.png"), NULL, NULL);
    renderWidget();
}

void EndScreen::updateScreen(float deltaTime)
{
    if (timePauseMusic != -1)
    {
        timePauseMusic -= deltaTime;
        if (timePauseMusic < 0 && Mix_PausedMusic())
        {
            Mix_ResumeMusic();
        }
    }
}

void EndScreen::handleEvent(const SDL_Event& event)
{
    handleWidgetEvent(event);
}

void EndScreen::createGUI()
{
    SDL_Point pos1; pos1.x = 555; pos1.y = 500;
    createButton("button_restart.png", pos1, std::bind(&EndScreen::goToGame, this));

    SDL_Point pos2; pos2.x = 555; pos2.y = 570;
    createButton("button_exit.png", pos2, []() { gQuit = true; });

    SDL_Point pos3; pos3.x = 1090; pos3.y = 10;
    createButton("button_home.png", pos3, std::bind(&EndScreen::goToMenu, this));
}

/*void EndScreen::createGUI()
{
    createButton("button_restart.png", { 555, 500 }, std::bind(&EndScreen::goToGame, this));
    createButton("button_exit.png", { 555, 570 }, []() { gQuit = true; });
    createButton("button_home.png", { 1090, 10 }, std::bind(&EndScreen::goToMenu, this));
}*/

void EndScreen::goToMenu()
{
    stateManager->switchScreen(StateManager::Screen::StartScreen);
}

void EndScreen::goToGame()
{
    stateManager->switchScreen(StateManager::Screen::GamePVP);
}