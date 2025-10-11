#include"stdafx.h"
#include "SettingScreen.h"

SettingScreen::SettingScreen(StateManager* stateManager) : GameScreen(stateManager)
{
	x_pos = 0;
	o_pos = 0;

	createGUI();
	stateManager->board = new Board();
	cell_o_assets.push_back("cell_o.png");
	cell_o_assets.push_back("cell_o_2.png");

	cell_x_assets.push_back("cell_x.png");
	cell_x_assets.push_back("cell_x_2.png");

	x_rect = new SDL_Rect();
	o_rect = new SDL_Rect();
	x_rect->x = SCREEN_WIDTH/2-40;
	x_rect->y = 200;
	x_rect->w = 80;
	x_rect->h = 80;

	o_rect->x = SCREEN_WIDTH/2-40;
	o_rect->y = 300;
	o_rect->w = 80;
	o_rect->h = 80;

	stateManager->time = 60;
}


SettingScreen::~SettingScreen()
{
	cell_x_assets.clear();
	cell_o_assets.clear();
	delete x_rect;
	delete o_rect;
}

void SettingScreen::renderScreen()
{
	//render background
	SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("setting_screen_background.png"), NULL, NULL);
	// render cell
	SDL_RenderCopy(gWindow->getRenderer(), stateManager->board->cell_x, NULL, x_rect);
	SDL_RenderCopy(gWindow->getRenderer(), stateManager->board->cell_o, NULL, o_rect);
	//render button
	renderWidget();

	//render time
	SDL_Texture* text;
	SDL_Rect time_rect;



	int settingTime = stateManager->time;
	std::stringstream ss;
	ss << "Time: ";
	ss << settingTime;
	std::string time = ss.str();
	text = AssetManager::getInstance()->getTextureFromText(time + ",orange-juice-2.0.ttf,60,255,255,255");
	SDL_QueryTexture(text, NULL, NULL, &time_rect.w, &time_rect.h);
	time_rect.x = (SCREEN_WIDTH - time_rect.w) / 2;
	time_rect.y = 410;
	SDL_RenderCopy(gWindow->getRenderer(), text, NULL, &time_rect);
}

void SettingScreen::updateScreen(float deltaTime)
{
}

void SettingScreen::handleEvent(const SDL_Event& event)
{
	handleWidgetEvent(event);
}

/*void SettingScreen::createGUI()
{
	createButton("button_start.png", { 555, 500 }, std::bind(&SettingScreen::startGame, this));
	createButton("button_back.png", { 555, 570 }, std::bind(&SettingScreen::gotoMenu, this));
	createButton("button_right.png", { 800, 200 }, std::bind(&SettingScreen::changeX, this, true));
	createButton("button_left.png", { 400, 200 }, std::bind(&SettingScreen::changeX, this, false));
	createButton("button_right.png", { 800, 300 }, std::bind(&SettingScreen::changeO, this, true));
	createButton("button_left.png", { 400, 300 }, std::bind(&SettingScreen::changeO, this, false));
	createButton("button_right.png", { 800, 400 }, std::bind(&SettingScreen::changeTime, this, true));
	createButton("button_left.png", { 400, 400 }, std::bind(&SettingScreen::changeTime, this, false));
}*/

void SettingScreen::createGUI()
{
    SDL_Point pos1; pos1.x = 555; pos1.y = 500;
    createButton("button_start.png", pos1, std::bind(&SettingScreen::startGame, this));

    SDL_Point pos2; pos2.x = 555; pos2.y = 570;
    createButton("button_back.png", pos2, std::bind(&SettingScreen::gotoMenu, this));

    SDL_Point pos3; pos3.x = 800; pos3.y = 200;
    createButton("button_right.png", pos3, std::bind(&SettingScreen::changeX, this, true));

    SDL_Point pos4; pos4.x = 400; pos4.y = 200;
    createButton("button_left.png", pos4, std::bind(&SettingScreen::changeX, this, false));

    SDL_Point pos5; pos5.x = 800; pos5.y = 300;
    createButton("button_right.png", pos5, std::bind(&SettingScreen::changeO, this, true));

    SDL_Point pos6; pos6.x = 400; pos6.y = 300;
    createButton("button_left.png", pos6, std::bind(&SettingScreen::changeO, this, false));

    SDL_Point pos7; pos7.x = 800; pos7.y = 400;
    createButton("button_right.png", pos7, std::bind(&SettingScreen::changeTime, this, true));

    SDL_Point pos8; pos8.x = 400; pos8.y = 400;
    createButton("button_left.png", pos8, std::bind(&SettingScreen::changeTime, this, false));
}


void SettingScreen::gotoMenu()
{
	stateManager->switchScreen(StateManager::Screen::StartScreen);
}

void SettingScreen::changeX(bool increase)
{
	if (increase)
	{
		x_pos = (x_pos + 1 + cell_x_assets.size()) % cell_x_assets.size();
		stateManager->board->cell_x = AssetManager::getInstance()->getTexture(cell_x_assets[x_pos]);
	}
	else
	{
		x_pos = (x_pos - 1 + cell_x_assets.size()) % cell_x_assets.size();
		stateManager->board->cell_x = AssetManager::getInstance()->getTexture(cell_x_assets[x_pos]);
	}
}

void SettingScreen::changeO(bool increase)
{
	if (increase)
	{
		o_pos = (o_pos + 1 + cell_o_assets.size()) % cell_o_assets.size();
		stateManager->board->cell_o = AssetManager::getInstance()->getTexture(cell_o_assets[o_pos]);
	}
	else
	{
		o_pos = (o_pos - 1 + cell_o_assets.size()) % cell_o_assets.size();
		stateManager->board->cell_o = AssetManager::getInstance()->getTexture(cell_o_assets[o_pos]);
	}
}

void SettingScreen::changeTime(bool increase)
{
	if (increase)
	{
		if (stateManager->time < 120) stateManager->time++;
	}
	else
	{
		if (stateManager->time > 30) stateManager->time--;
	}
}


void SettingScreen::startGame()
{
	stateManager->switchScreen(StateManager::Screen::GamePVP);
}