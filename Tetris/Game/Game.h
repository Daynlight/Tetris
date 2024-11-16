#pragma once 
#include "../Renderer/Renderer.h"
#include "../vendor/Data/Data.h"
#include <chrono>

class Tetris{
public:
  Tetris(Window* window, Uint8 rows, Uint8 columns, Uint32 cell_size, Uint32 tick_speed);
  void Run();
  void Clear();
  bool IsEnded();
  void TetrisEvent(SDL_Event event);
private:
  Window* window;
  bool is_ended = false;
  std::chrono::time_point<std::chrono::high_resolution_clock> last;
  Uint32 tick_speed;
  Uint8 current_block_position;
  Uint8 current_block_height = 0;
  Uint8 rows, columns;
  Uint32 cell_size;
};


class App{
private:
  enum State{
    Home,
    GameStarting,
    GameRunning,
    GameEnded
  };
public:
  App(Window *window, Data::File *leaderboard, const Uint8 rows, const Uint8 columns, const Uint32 cell_size, Uint32 tick_speed);
  void Run();
private:
  void RenderHome();
  void AppEvent();
  State game_state = Home;
  Data::File *leaderboard;
  Window *window;
  Tetris tetris;

};