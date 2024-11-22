#pragma once
#include "../Settings.h"
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

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
  void renderTexture(int x, int y, int w, int h, SDL_Texture *texture);
  std::pair<int, int> getTextSize(std::string text);
  SDL_Texture *createTextTexture(std::string text);

  const bool isRunning();
  const SDL_Rect getWindowPositionAndSize();
private:
  TTF_Font* font;
  bool running = true;
  SDL_Window *window;
  SDL_Renderer *renderer;
};