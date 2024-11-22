#pragma once 
#include "../Settings.h"
#include "../Renderer/Renderer.h"
#include "Tetris.h"
#include "../vendor/Data/Data.h"

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