#pragma once 
#include "../Renderer/Renderer.h"
#include "../vendor/Data/Data.h"

class App{
private:
  enum State{
    Home,
    GameRunning,
    GameEnded
  };
public:
  App(Window *window, Data::File *leaderboard, const Uint8 rows, const Uint8 columns, const Uint32 cell_size);
  void Run();
private:
  void RenderHome();
  void AppEvent();
  State game_state = GameRunning;
  Data::File *leaderboard;
  Window *window;
  const Uint8 rows, columns;
  const Uint32 cell_size;
};

class Tetris{
public:
  Tetris(Window* window, Uint8 rows, Uint8 columns, Uint32 cell_size);
  void Run();
  void Clear();
  bool IsEnded();
private:
  Window* window;
  Uint8 rows, columns;
  Uint32 cell_size;
};