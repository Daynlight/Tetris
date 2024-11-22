#include "App.h"

App::App(Window *window, Data::File *leaderboard)
  :window(window), leaderboard(leaderboard), tetris(window) { 
    leaderboard_render = window->createTextTexture((*leaderboard)[0]);
    leaderboard_sizes = window->getTextSize((*leaderboard)[0]);
  }

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
      if(std::stoi((*leaderboard)[0]) < tetris.getPoints()){
        leaderboard->pop();
        leaderboard->push(std::to_string(tetris.getPoints()));
        leaderboard_render = window->createTextTexture((*leaderboard)[0]);
        leaderboard_sizes = window->getTextSize((*leaderboard)[0]);
      }
        
      game_state = Home;
      break;
    };

    appEvent(); 
    window->render();
  }
}

void App::renderHome(){
  SDL_Rect window_size = window->getWindowPositionAndSize();
    window->renderTexture((window_size.w - leaderboard_sizes.first)/2, 
    (window_size.h - leaderboard_sizes.second)/2, leaderboard_sizes.first, 
    leaderboard_sizes.second, leaderboard_render);
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

