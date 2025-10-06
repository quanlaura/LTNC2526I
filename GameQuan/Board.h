#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "AssetManager.h"
#include "AI.h"
#include "Settings.h"
#include "Window.h"

//bien toan cuc duoc dinnh nghia o file khac
extern Window* gWindow;
extern bool gSoundOn;

class Board
{
private:
	SDL_Texture* cell_empty;
	SDL_Texture* cell_mouse_state;
	SDL_Texture* win_horizontal;
	SDL_Texture* win_down;
	SDL_Texture* win_up;
	SDL_Texture* win_vertical;
	SDL_Texture* current_move;
	pair<int, int> current_move_pos;
	int gameBoard[BOARD_WIDTH][BOARD_HEIGHT];
	GomokuAI* gomokuAI;
	SDL_Rect cell_rect;
	Mix_Chunk* moveSound;

public:
	bool isGamePVE;
	bool moved;
	SDL_Texture* cell_x;
	SDL_Texture* cell_o;
	void getGameBoard(int** board)
	{
		for (int i = 0; i < BOARD_WIDTH; i++) {
			for (int j = 0; j < BOARD_HEIGHT; j++) {
				board[i][j] = gameBoard[i][j];
			}

		}

	}
	Board();
	~Board();
	void renderMouseState(int x, int y);
	void renderBoard();
	void move(int x, int y);
	void handleBoardEvent();
	void reset();
	int isWin(int row, int col);
	int winner;
	SDL_Rect rect;
	SDL_Texture* win_case;
	int nextMove;
};
