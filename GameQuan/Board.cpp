#include "stdafx.h"
#include "Board.h"
#include <vector>

using namespace std;

Board::Board()
{
	moved = false;
	winner = 0;
	nextMove = O_CELL;
	gomokuAI = new GomokuAI(4);
	moveSound = AssetManager::getInstance() -> getSoundBuffer("button_click_sound.wav");
	cell_empty = AssetManager::getInstance() ->getTexture("cell_empty.png");
	cell_x = AssetManager::getInstance() -> getTexture("cell_x.png");
	cell_o = AssetManager::getInstance() -> getTexture("cell_o.png");
	cell_mouse_state = AssetManager::getInstance() -> getTexture("cell_mouse_state.png");
	win_up = AssetManager::getInstance() -> getTexture("win_up.png");
	win_down = AssetManager::getInstance() -> getTexture("win_down.png");
	win_horizontal = AssetManager::getInstance() -> getTexture("win_horizontal.png");
	win_vertical = AssetManager::getInstance() -> getTexture("win_vertical.png");
	current_move = AssetManager::getInstance() -> getTexture("current_move.png");
	cell_rect.w = 40;
	cell_rect.h = 40;
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			gameBoard[i][j] = 0;
		}

	}

}

Board::~Board()
{
	SDL_DestroyTexture(cell_empty);
	SDL_DestroyTexture(cell_x);
	SDL_DestroyTexture(cell_o);
	SDL_DestroyTexture(cell_mouse_state);
	SDL_DestroyTexture(win_up);
	SDL_DestroyTexture(win_down);
	SDL_DestroyTexture(win_horizontal);
	SDL_DestroyTexture(win_vertical);
	SDL_DestroyTexture(current_move);
}

void Board::reset()
{
	for (int i = 0; i <BOARD_WIDTH; i++) {
		for (int j = 0; j <BOARD_HEIGHT; j++) {
			gameBoard[i][j] = 0;
		}

	}
	winner = 0;
	nextMove = O_CELL;
}

void Board::renderMouseState(int x, int y)
{
	int cell_pos_x, cell_pos_y;
	cell_pos_x = (x - BOARD_X) / 40;
	cell_pos_y = (y - BOARD_Y) / 40;

	if (cell_pos_y >= 0 && cell_pos_y < BOARD_HEIGHT && cell_pos_x >= 0 && cell_pos_x < BOARD_WIDTH
		&& x - BOARD_X > 0 && y - BOARD_Y > 0) {
			cell_rect.x = cell_pos_x * 40 + BOARD_X;
			cell_rect.y = cell_pos_y * 40 + BOARD_Y;
			SDL_RenderCopy(gWindow -> getRenderer(), cell_mouse_state, NULL, &cell_rect);
	}

}

void Board::renderBoard()
{
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			cell_rect.x = i * 40 + BOARD_X;
			cell_rect.y = j * 40 + BOARD_Y;
			if (gameBoard[i][j] == 0) {
				SDL_RenderCopy(gWindow -> getRenderer(), cell_empty, NULL, &cell_rect);
			}
			else if (gameBoard[i][j] == 1) {
				SDL_RenderCopy(gWindow -> getRenderer(), cell_x, NULL, &cell_rect);
			}
			else {
				SDL_RenderCopy(gWindow -> getRenderer(), cell_o, NULL, &cell_rect);
			}

		}

	}
	//render the current move
	if (current_move_pos.first >= 0 && current_move_pos.second >= 0)
	{
		cell_rect.x = current_move_pos.first * 40 + BOARD_X;
		cell_rect.y = current_move_pos.second * 40 + BOARD_Y;
		SDL_RenderCopy(gWindow -> getRenderer(), current_move, NULL, &cell_rect);
	}
	int x, y;
	SDL_GetMouseState(&x, &y);
	renderMouseState(x, y);
}

void Board::move(int col, int row)
{
	if (row >= 0 && row < BOARD_HEIGHT && col >= 0 && col < BOARD_WIDTH && gameBoard[col][row] == EMPTY_CELL)
	{
		current_move_pos.first = col;
		current_move_pos.second = row;
		if (gSoundOn)
		{
			Mix_PlayChannel(-1,moveSound, 0);
		}
		gameBoard[col][row] = nextMove;
		nextMove = (nextMove == O_CELL) ? X_CELL : O_CELL;
		winner = isWin(col, row);
	}

}

void Board::handleBoardEvent()
{
	if (isGamePVE && nextMove == X_CELL)
	{
		pair<int, int> AI_move = gomokuAI -> bestMove(gameBoard);
		move(AI_move.first, AI_move.second);
		//cout << "AI moved" << endl;
		moved = true;
	}
	else {
		int x, y;
		SDL_GetMouseState(&x, &y);
		x -= BOARD_X;
		y -= BOARD_Y;
		if (x >= 0 && x < BOARD_WIDTH * 40 && y >= 0 && y < BOARD_HEIGHT * 40)
		{
			move (x/40, y / 40);
			moved = true;
		}

	}

}

int Board::isWin(int col, int row)
{
    int x, y, cnt;
    vector<pair<int, int>> moved;

    // check cheo xuong
    cnt = 1;
    moved.clear();
    x = col;
    y = row;

    while (col + 1 < BOARD_WIDTH && row + 1 < BOARD_HEIGHT && gameBoard[x + 1][y + 1] == gameBoard[col][row]) {
        x++;
        y++;
        cnt++;
        moved.push_back(make_pair(x, y));
    }
    moved.push_back(make_pair(col, row));

    x = col;
    y = row;
    while (col - 1 >= 0 && row - 1 >= 0 && gameBoard[x - 1][y - 1] == gameBoard[col][row]) {
        x--;
        y--;
        cnt++;
        moved.push_back(make_pair(x, y));
    }
    if (cnt >= 5) {
        rect.x = moved[moved.size() - 1].first * 40 + BOARD_X;
        rect.y = moved[moved.size() - 1].second * 40 + BOARD_Y;
        rect.w = 200;
        rect.h = 200;
        SDL_RenderCopy(gWindow->getRenderer(), win_down, NULL, &rect);
        win_case = win_down;
        return nextMove;
    }

    // check ngang
    cnt = 1;
    moved.clear();
    x = col;
    y = row;

    while (col + 1 < BOARD_WIDTH && gameBoard[x + 1][y] == gameBoard[col][row]) {
        x++;
        cnt++;
        moved.push_back(make_pair(x, y));
    }
    moved.push_back(make_pair(col, row));

    x = col;
    y = row;
    while (col - 1 >= 0 && gameBoard[x - 1][y] == gameBoard[col][row]) {
        x--;
        cnt++;
        moved.push_back(make_pair(x, y));
    }
    if (cnt >= 5) {
        rect.x = moved[moved.size() - 1].first * 40 + BOARD_X;
        rect.y = moved[moved.size() - 1].second * 40 + BOARD_Y - 80;
        rect.w = 200;
        rect.h = 200;
        SDL_RenderCopy(gWindow->getRenderer(), win_horizontal, NULL, &rect);
        win_case = win_horizontal;
        return nextMove;
    }

    // check doc
    cnt = 1;
    moved.clear();
    x = col;
    y = row;

    while (row + 1 < BOARD_HEIGHT && gameBoard[x][y + 1] == gameBoard[col][row]) {
        y++;
        cnt++;
        moved.push_back(make_pair(x, y));
    }
    moved.push_back(make_pair(col, row));

    x = col;
    y = row;
    while (row - 1 >= 0 && gameBoard[x][y - 1] == gameBoard[col][row]) {
        y--;
        cnt++;
        moved.push_back(make_pair(x, y));
    }
    if (cnt >= 5) {
        rect.x = moved[moved.size() - 1].first * 40 + BOARD_X - 80;
        rect.y = moved[moved.size() - 1].second * 40 + BOARD_Y;
        rect.w = 200;
        rect.h = 200;
        SDL_RenderCopy(gWindow->getRenderer(), win_vertical, NULL, &rect);
        win_case = win_vertical;
        return nextMove;
    }

    // check cheo len
    cnt = 1;
    moved.clear();
    x = col;
    y = row;

    while (col + 1 < BOARD_WIDTH && row - 1 >= 0 && gameBoard[x + 1][y - 1] == gameBoard[col][row]) {
        x++;
        y--;
        cnt++;
        moved.push_back(make_pair(x, y));
    }
    moved.push_back(make_pair(col, row));

    x = col;
    y = row;
    while (col - 1 >= 0 && row + 1 < BOARD_HEIGHT && gameBoard[x - 1][y + 1] == gameBoard[col][row]) {
        x--;
        y++;
        cnt++;
        moved.push_back(make_pair(x, y));
    }
    if (cnt >= 5) {
        rect.x = moved[moved.size() - 1].first * 40 + BOARD_X;
        rect.y = moved[moved.size() - 1].second * 40 + BOARD_Y - 160;
        rect.w = 200;
        rect.h = 200;
        SDL_RenderCopy(gWindow->getRenderer(), win_up, NULL, &rect);
        win_case = win_up;
        return nextMove;
    }

    return 0;
}






