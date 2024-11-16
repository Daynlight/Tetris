#pragma once
#include <SDL.h>

class Window{
public:
  Window(const char* title, int x, int y, int w, int h, SDL_WindowFlags flags);
  void RenderFrame();
  SDL_Event GetEvent();
  bool running = true;
private:
  SDL_Event *event;
  SDL_Window *window;
  SDL_Renderer *renderer;
};