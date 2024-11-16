#pragma once 
#include "../Renderer/Renderer.h"
#include "../vendor/Data/Data.h"

class App{
public:
  App(Window *window, Data::File *leaderboard);
  void Run();
private:
  void AppEvent();
  Data::File *leaderboard;
  Window *window;
};

