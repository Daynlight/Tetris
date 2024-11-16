#pragma once 
#include "../Renderer/Renderer.h"

class App{
public:
  App(Window *window);
  void Run();
private:
  bool isRunning = true;
  Window *window;
};

