#include "Renderer.h"

Window::Window(const char *title, int x, int y, int w, int h, SDL_WindowFlags flags){
    window = SDL_CreateWindow(title, x, y, w, h, flags);
    renderer = SDL_CreateRenderer(window, NULL, NULL);
}

void Window::RenderFrame(){

}

SDL_Event Window::GetEvent() {
  
  return SDL_Event();
}
