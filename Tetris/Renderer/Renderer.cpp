#include "Renderer.h"

Window::Window(int x, int y, int w, int h){
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  font = TTF_OpenFont(FONTNAME.c_str(), FONTSIZE);
  window = SDL_CreateWindow(TITLE, x, y, w, h, WINDOWFLAGS);
  renderer = SDL_CreateRenderer(window, 0, 0);
}

void Window::windowEvent(SDL_Event event){
  switch (event.type) {
      case SDL_QUIT:
          running = false;
          break;
  }
}

const bool Window::isRunning(){
  return running;
}

const SDL_Rect Window::getWindowPositionAndSize(){
  SDL_Rect rect;
  SDL_GetWindowPosition(window, &rect.x, &rect.y);
  SDL_GetWindowSize(window, &rect.w, &rect.h);
  return rect;
}

void Window::render(){
  SDL_RenderPresent(renderer);
}

void Window::background(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
  SDL_RenderClear(renderer);
}

void Window::renderSquare(SDL_Rect *box, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
  SDL_RenderDrawRect(renderer, box);
}

void Window::renderSquare(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
  SDL_Rect box(x, y, w, h);
  renderSquare(&box, r, g, b, a);
}

void Window::renderFillSquare(SDL_Rect *box, Uint8 r, Uint8 g, Uint8 b, Uint8 a){
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
  SDL_RenderFillRect(renderer, box);
}

void Window::renderFillSquare(int x, int y, int w, int h, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  SDL_Rect box(x, y, w, h);
  renderFillSquare(&box, r, g, b, a);
}

void Window::renderTexture(int x, int y, int w, int h, SDL_Texture *texture){
  SDL_Rect rect = SDL_Rect(x, y, w, h);
  SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

std::pair<int, int> Window::getTextSize(std::string text){
  int w = 0,  h = 0;
  TTF_SizeText(font, text.c_str(), &w, &h);
  return std::pair<int, int>(w, h);
}

SDL_Texture *Window::createTextTexture(std::string text) {
  SDL_Surface * surface = TTF_RenderText_Blended(font, text.c_str(), SDL_Colour(255,255,255,255));
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  return texture;
}
