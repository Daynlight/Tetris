#pragma once
#include <SDL.h>

class Window{
public:
  Window(const char* title, int x, int y, int w, int h, SDL_WindowFlags flags);
  void WindowEvent(SDL_Event event);
  void Background(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0);
  void Render();

  void RenderSquare(SDL_Rect *box, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0);
  void RenderSquare(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0);
  void RenderFillSquare(SDL_Rect *box, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0);
  void RenderFillSquare(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0);
  
  const bool IsRunning();
  const SDL_Rect GetWindowPositionAndSize();
private:
  bool running = true;
  SDL_Window *window;
  SDL_Renderer *renderer;
};