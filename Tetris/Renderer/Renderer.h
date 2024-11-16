#pragma once
#include <SDL.h>

class Window{
public:
  Window(const char* title, int x, int y, int w, int h, SDL_WindowFlags flags);
  void WindowEvent(SDL_Event event);
  bool IsRunning();
  void Background(Uint8 r, Uint8 g, Uint8 b);
  void Render();
private:
  bool running = true;
  SDL_Window *window;
  SDL_Renderer *renderer;
};