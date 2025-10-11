#include "stdafx.h"
#include "GamePVP.h"

GamePVP::GamePVP(StateManager* stateManager) : GameScreen(stateManager)
{
    stateManager->timeOut = stateManager->time;
	pause = false;
	createGUI();
    stateManager->board->reset();
	stateManager->board->isGamePVE = false;
}

GamePVP::~GamePVP()
{
	delete pauseButton;
	delete resumeButton;
	SDL_DestroyTexture(text);
}

void GamePVP::renderScreen()
{
    //render background
    SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("game_pvp_background.png"), NULL, NULL);
	//render board
	stateManager->board->renderBoard();
	//render winner
    if (stateManager->board->winner != 0)
    {
        SDL_RenderCopy(gWindow->getRenderer(), stateManager->board->win_case, NULL, &stateManager->board->rect);
    }
    //render time
	std::stringstream ss;
	ss << "Thinking time: ";
	ss << (int)stateManager->timeOut;
	std::string time = ss.str();
	text = AssetManager::getInstance()->getTextureFromText(time + ",orange-juice-2.0.ttf,60,255,255,255");
	SDL_QueryTexture(text, NULL, NULL, &time_rect.w, &time_rect.h);
	time_rect.x = (SCREEN_WIDTH - time_rect.w) / 2;
	time_rect.y = 10;
	SDL_RenderCopy(gWindow->getRenderer(), text, NULL, &time_rect);
	//render button

    renderWidget();

    if (pause)
    {
        resumeButton->render();
    }
    else
    {
        pauseButton->render();
    }
}

void GamePVP::updateScreen(float deltaTime)
{
    if (!pause)
    {
        stateManager->timeOut -= deltaTime;
        if (stateManager->timeOut < 0)
        {
            stateManager->board->winner = stateManager->board->nextMove;
        }

        if (stateManager->board->winner != 0)
        {
            SDL_Delay(3000);
            stateManager->switchScreen(StateManager::Screen::EndScreen);
        }
    }
}

void GamePVP::handleEvent(const SDL_Event& event)
{
    if (pause)
    {
        resumeButton->handleEvent(event);
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
        {
            pause = false;
        }
    }
    else
    {
        pauseButton->handleEvent(event);
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
        {
            pause = true;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            stateManager->board->handleBoardEvent();
			if (stateManager->board->moved)
			{
				stateManager->timeOut = stateManager->time;
				stateManager->board->moved = false;
			}
        }
    }
    handleWidgetEvent(event);
}

/*void GamePVP::createGUI()
{
    createButton("button_home.png", { 1090, 10 }, std::bind(&GamePVP::goToMenu, this));
    pauseButton = new Button("button_pause.png", { 115, 15 }, std::bind(&GamePVP::switchPause, this));
    resumeButton = new Button("button_resume.png", { 115, 15 }, std::bind(&GamePVP::switchPause, this));
}*/

void GamePVP::createGUI()
{
    SDL_Point pos1; pos1.x = 1090; pos1.y = 10;
    createButton("button_home.png", pos1, std::bind(&GamePVP::goToMenu, this));

    SDL_Point pos2; pos2.x = 115; pos2.y = 15;
    pauseButton = new Button("button_pause.png", pos2, std::bind(&GamePVP::switchPause, this));

    SDL_Point pos3; pos3.x = 115; pos3.y = 15;
    resumeButton = new Button("button_resume.png", pos3, std::bind(&GamePVP::switchPause, this));
}

void GamePVP::goToMenu()
{
    stateManager->switchScreen(StateManager::Screen::StartScreen);
}

void GamePVP::switchPause()
{
    if (pause)
    {
        pause = false;
    }
    else
    {
        pause = true;
    }
}