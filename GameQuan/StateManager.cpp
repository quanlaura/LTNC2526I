#include "stdafx.h"

#include "StateManager.h"
#include "GameScreen.h"
#include "StartScreen.h"
#include "GamePVP.h"
#include "EndScreen.h"
#include "SettingScreen.h"
#include "GamePVE.h"
#include "PveEndScreen.h"
#include "PveSettingScreen.h"
#include "AboutScreen.h"
#include <iostream>

StateManager::StateManager()
{
	time = 60;
}

StateManager::~StateManager()
{
	delete currentScreen;
	delete nextScreen;
}

void StateManager::switchScreen(Screen newScreen)
{
	if (nextScreen != nullptr)
	{
		nextScreen = nullptr;
	}
	switch (newScreen)
	{
	case Screen::StartScreen:
		nextScreen = new StartScreen(this);
		break;
	case Screen::GamePVP:
		nextScreen = new GamePVP(this);
		break;
	case Screen::EndScreen:
		nextScreen = new EndScreen(this);
		break;
	case Screen::SettingScreen:
		nextScreen = new SettingScreen(this);
		break;
	case Screen::GamePVE:
		nextScreen = new GamePVE(this);
		break;
	case Screen::PveEndScreen:
		nextScreen = new PveEndScreen(this);
		break;
	case Screen::PveSettingScreen:
		nextScreen = new PveSettingScreen(this);
		break;
	case Screen::AboutScreen:
		nextScreen = new AboutScreen(this);
		break;
	default:
		break;
	}

	if (nextScreen != nullptr)
	{
		std::swap(currentScreen, nextScreen);
	}
}