#include "Game.h"

App::App(Window *window)
  :window(window) { }

void App::Run(){
  while(window->IsRunning()){
    window->Background(255,255,255);

    AppEvent(); 
    window->Render();
  }
}

void App::AppEvent(){
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    switch(event.type){
      
      default:
        window->WindowEvent(event);
        break;
      
    }
  }
}
