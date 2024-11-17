#include "Game.h"

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
      tetris.clear();
      game_state = GameRunning;
      break;
      case GameRunning:
      tetris.run();
      if(!tetris.isRunning()) game_state = GameEnded;
      break;
      case GameEnded:
      tetris.clear();
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

Tetris::Tetris(Window* window)
  :window(window), current_block_position(ROWS/2) {
    last = std::chrono::high_resolution_clock::now();
  }

void Tetris::run(){
  // Canva
  SDL_Rect canva = window->getWindowPositionAndSize();
  canva.y = (canva.h - CELLSIZE*COLUMNS)/2;
  canva.x = (canva.w - CELLSIZE*ROWS) - canva.y;
  canva.w = CELLSIZE*ROWS;
  canva.h = CELLSIZE*COLUMNS;
  window->renderFillSquare(canva.x, canva.y, canva.w, canva.h, 255, 255, 255);

  // block
  window->renderFillSquare(current_block_position * CELLSIZE + canva.x, canva.y + current_block_height*CELLSIZE, 
  CELLSIZE, CELLSIZE, 255, 0, 0);

  // Clock Sync
  std::chrono::time_point now = std::chrono::high_resolution_clock::now();
  std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - last);
  if(duration.count() > TICKSPEED) {
    if(current_block_height < COLUMNS - 1) current_block_height++;
    else {
      current_block_height = 0;
      current_block_position = ROWS/2;
    };
    last = std::chrono::high_resolution_clock::now();
  }
}

void Tetris::clear(){
  last = std::chrono::high_resolution_clock::now();
}

bool Tetris::isRunning(){
  return running;
}

void Tetris::tetrisEvent(SDL_Event event){
  switch (event.type){
  case SDL_KEYDOWN:
    if(event.key.keysym.sym == SDLK_LEFT && current_block_position > 0) current_block_position--;
    if(event.key.keysym.sym == SDLK_RIGHT && current_block_position < ROWS - 1) current_block_position++;
    break;
  }
}
