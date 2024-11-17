#pragma once
#include "../Settings.h"
#include <SDL.h>

class Window{
public:
  Window(int x, int y, int w, int h);
  void windowEvent(SDL_Event event);
  void render();

  void background(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0);
  void renderSquare(SDL_Rect *box, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0);
  void renderSquare(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0);
  void renderFillSquare(SDL_Rect *box, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0);
  void renderFillSquare(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 0);

  const bool isRunning();
  const SDL_Rect getWindowPositionAndSize();
private:
  bool running = true;
  SDL_Window *window;
  SDL_Renderer *renderer;
};