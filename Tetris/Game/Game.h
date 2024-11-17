#pragma once 
#include "../Settings.h"
#include "../Renderer/Renderer.h"
#include "../vendor/Data/Data.h"
#include <chrono>

class Tetris{
public:
  Tetris(Window* window);
  void run();
  void clear();
  bool isRunning();
  void tetrisEvent(SDL_Event event);
private:
  Window* window;
  bool running = true;
  std::chrono::time_point<std::chrono::high_resolution_clock> last;
  Uint8 current_block_position;
  Uint8 current_block_height = 0;
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
  App(Window *window, Data::File *leaderboard);
  void run();
private:
  void renderHome();
  void appEvent();
  State game_state = Home;
  Data::File *leaderboard;
  Window *window;
  Tetris tetris;

};