#include "Game.h"

App::App(Window *window, Data::File *leaderboard, const Uint8 rows, const Uint8 columns, const Uint32 cell_size)
  :window(window), leaderboard(leaderboard), tetris(window, rows, columns, cell_size) {
   }

void App::Run(){
  while(window->IsRunning()){
    window->Background(20,20,20);
    
    switch(game_state){
      case Home:
      RenderHome();
      break;
      case GameStarting:
      tetris.Clear();
      game_state = GameRunning;
      break;
      case GameRunning:
      tetris.Run();
      if(tetris.IsEnded()) game_state = GameEnded;
      break;
      case GameEnded:
      tetris.Clear();
      game_state = Home;
      break;
    };

    AppEvent(); 
    window->Render();
  }
}

void App::RenderHome(){
}

void App::AppEvent()
{
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    switch(event.type){
      case SDL_KEYDOWN:
        if(event.key.keysym.sym == SDLK_RETURN) game_state = GameStarting;
      
    }
    tetris.TetrisEvent(event);
    window->WindowEvent(event);
  }
}

Tetris::Tetris(Window* window, Uint8 rows, Uint8 columns, Uint32 cell_size)
  :window(window), rows(rows), columns(columns), cell_size(cell_size), current_block_position(rows/2) {
    last = std::chrono::high_resolution_clock::now();
  }

void Tetris::Run(){
  // Canva
  SDL_Rect canva = window->GetWindowPositionAndSize();
  canva.y = 0;
  canva.x = (canva.w - cell_size*rows)/2;
  canva.w = cell_size*rows;
  canva.h = cell_size*columns;
  window->RenderFillSquare(canva.x, canva.y, canva.w, canva.h, 255, 255, 255);

  // block
  window->RenderFillSquare(current_block_position * cell_size + canva.x, canva.y + current_block_height*cell_size, 
  cell_size, cell_size, 255, 0, 0);


  // Clock Sync
  std::chrono::time_point now = std::chrono::high_resolution_clock::now();
  std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - last);
  if(duration.count() > 1000) {
    if(current_block_height < columns - 1) current_block_height++;
    else current_block_height = 0;
    last = std::chrono::high_resolution_clock::now();
  }
}

void Tetris::Clear(){
}

bool Tetris::IsEnded(){
  return is_ended;
}

void Tetris::TetrisEvent(SDL_Event event){
  switch (event.type){
  case SDL_KEYDOWN:
    if(event.key.keysym.sym == SDLK_LEFT && current_block_position > 0) current_block_position--;
    if(event.key.keysym.sym == SDLK_RIGHT && current_block_position < rows - 1) current_block_position++;
    break;
  }
}
