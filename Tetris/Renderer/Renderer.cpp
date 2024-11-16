#include "Renderer.h"

Window::Window(const char *title, int x, int y, int w, int h, SDL_WindowFlags flags){
    window = SDL_CreateWindow(title, x, y, w, h, flags);
    renderer = SDL_CreateRenderer(window, 0, 0);
}

void Window::WindowEvent(SDL_Event event){
  switch (event.type) {
      case SDL_QUIT:
          running = false;
          break;
  }
}

const bool Window::IsRunning(){
  return running;
}

const SDL_Rect Window::GetWindowPositionAndSize(){
  SDL_Rect rect;
  SDL_GetWindowPosition(window, &rect.x, &rect.y);
  SDL_GetWindowSize(window, &rect.w, &rect.h);
  return rect;
}

void Window::Background(Uint8 r, Uint8 g, Uint8 b){
    SDL_SetRenderDrawColor(renderer, r, g, b, 0);
    SDL_RenderClear(renderer);
}

void Window::Render(){
  SDL_RenderPresent(renderer);
}
