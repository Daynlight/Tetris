#include "Game.h"

App::App(Window *window, Data::File *leaderboard)
  :window(window), leaderboard(leaderboard) { }

void App::Run(){
  while(window->IsRunning()){
    window->Background(20,20,20);
    window->RenderFillSquare(100, 100, 50, 50, 255, 0, 0);

    AppEvent(); 
    window->Render();
  }
}

void App::AppEvent(){
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    switch(event.type){
      
      default:
        break;
      
    }
    window->WindowEvent(event);
  }
}
