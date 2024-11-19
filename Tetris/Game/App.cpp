#include "App.h"

App::App(Window *window, Data::File *leaderboard)
  :window(window), leaderboard(leaderboard), tetris(window) { }

void App::run(){
  while(window->isRunning()){
    window->background(20,20,20);
    
    switch(game_state){
      case Home:
      renderHome();
      break;
      case GameStarting:
      tetris.start();
      game_state = GameRunning;
      break;
      case GameRunning:
      tetris.run();
      if(!tetris.isRunning()) game_state = GameEnded;
      break;
      case GameEnded:
      game_state = Home;
      break;
    };

    appEvent(); 
    window->render();
  }
}

void App::renderHome(){
}

void App::appEvent()
{
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    switch(event.type){
      case SDL_KEYDOWN:
        if(event.key.keysym.sym == SDLK_RETURN) game_state = GameStarting;
    }
    tetris.tetrisEvent(event);
    window->windowEvent(event);
  }
}

