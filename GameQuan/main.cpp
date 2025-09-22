#include"stdafx.h"
#include <SDL.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    // Khởi tạo SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Không thể khởi tạo SDL! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }

    // Tạo cửa sổ
    SDL_Window* window = SDL_CreateWindow(
        "Cua so SDL2 test",          // tiêu đề
        SDL_WINDOWPOS_CENTERED,      // vị trí X
        SDL_WINDOWPOS_CENTERED,      // vị trí Y
        640,                         // chiều rộng
        480,                         // chiều cao
        SDL_WINDOW_SHOWN             // hiển thị
    );

    if (window == nullptr) {
        cout << "Không thể tạo cửa sổ! SDL_Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    // Vòng lặp sự kiện (chờ người dùng đóng cửa sổ)
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) { // Nhấn nút X
                quit = true;
            }
        }
        // Bạn có thể thêm render ở đây
    }

    // Giải phóng
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
