#include "Tetris.h"

Tetris::Tetris(Window* window)
  :window(window) {
  initBlockVariants();
  start();
}

void Tetris::createBlockVariant(std::initializer_list<std::pair<int, int>> list) {
  blocks_variants.emplace_back(window, ROWS/2, 0, list);
}

size_t Tetris::random(size_t x) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, x);
  return distrib(gen);
}

void Tetris::run(){
  SDL_Rect canva = window->getWindowPositionAndSize();
  canva.y = (canva.h - CELLSIZE*COLUMNS)/2;
  canva.x = (canva.w - CELLSIZE*ROWS) - canva.y;
  canva.w = CELLSIZE*ROWS;
  canva.h = CELLSIZE*COLUMNS;
  window->renderFillSquare(canva.x, canva.y, canva.w, canva.h, 255, 255, 255);

  for(Block &block : blocks)
    block.render(canva);

  std::chrono::time_point now = std::chrono::high_resolution_clock::now();
  std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - last);
  if(duration.count() > TICKSPEED) {
    bool colision = false;
    for(int i = 0; i < blocks.size() - 1; i++){
      colision = blocks[i].colisionWithBlock(blocks[blocks.size() - 1], std::pair<int,int>(0, 1));
      if(colision) break;
    }
      
    if(!blocks[blocks.size() - 1].colisionY(COLUMNS - 1) && !colision) blocks[blocks.size() - 1].y++;
    else {
      bool checking = 0;
      do{
        checking = 0;
        for(int i = COLUMNS - 1; i > 0; i--){
          int rows_element = 0;
          for(Block & block : blocks)
            for(std::pair<int, int> &el : block.blocks)
              if(block.y + el.second == i) rows_element++;
              
          if(rows_element == ROWS){
            checking = 1;
          for(Block & block : blocks)
            for(int j = 0; j < block.blocks.size(); j++)
              if(block.y + block.blocks[j].second == i) {
                block.blocks.erase(block.blocks.begin() + j);
                j--;
              }
              for(Block &move_block : blocks)
                for(std::pair<int, int> &el2 : move_block.blocks)
                  if(move_block.y + el2.second <= i) el2.second++;
          }
        }
      } while(checking);

      blocks.emplace_back(blocks_variants[random(blocks_variants.size() - 1)]);
      blocks[blocks.size() - 1].colour = colour_variants[random(colour_variants.size() - 1)];
      bool colision = false;
      for(int i = 0; i < blocks.size() - 1; i++){
        colision = blocks[i].colisionWithBlock(blocks[blocks.size() - 1], std::pair<int,int>(0, 1));
        if(colision) break;
      }
      if(colision) running = false;
    }
    last = std::chrono::high_resolution_clock::now();
  }
}

void Tetris::start(){
  blocks.clear();
  blocks.emplace_back(blocks_variants[random(blocks_variants.size() - 1)]);
  blocks[blocks.size() - 1].colour = colour_variants[random(colour_variants.size() - 1)];
  running = true;
  points = 0;
  last = std::chrono::high_resolution_clock::now();
}

bool Tetris::isRunning(){ return running; }

void Tetris::tetrisEvent(SDL_Event event){
  switch (event.type){
  case SDL_KEYDOWN:
    if(event.key.keysym.sym == SDLK_a && !blocks[blocks.size() - 1].colisionX(0)){
      bool colision = false;
      for(int i = 0; i < blocks.size() - 1; i++){
        colision = blocks[i].colisionWithBlock(blocks[blocks.size() - 1], std::pair<int,int>(-1, 0)); if(colision) break;
      }
      if(!colision) blocks[blocks.size() -1].x--;
    }
    if(event.key.keysym.sym == SDLK_d && !blocks[blocks.size() - 1].colisionX(ROWS - 1)) {
      bool colision = false;
      for(int i = 0; i < blocks.size() - 1; i++){
        colision = blocks[i].colisionWithBlock(blocks[blocks.size() - 1], std::pair<int,int>(1, 0)); if(colision) break;
      }
      if(!colision) blocks[blocks.size() -1].x++;
    }
    if(event.key.keysym.sym == SDLK_s && !blocks[blocks.size() - 1].colisionY(COLUMNS - 1)) {
      bool colision = false;
      for(int i = 0; i < blocks.size() - 1; i++){
        colision = blocks[i].colisionWithBlock(blocks[blocks.size() - 1], std::pair<int,int>(0, 1)); if(colision) break;
        colision = blocks[blocks.size() - 1].colisionY(COLUMNS - 1); if(colision) break;
        last = std::chrono::high_resolution_clock::now();
      }
      if(!colision) blocks[blocks.size() -1].y++;
    }
    if(event.key.keysym.sym == SDLK_e){
      blocks[blocks.size() - 1].rotate(-1);
      bool colision = false;
      for(int i = 0; i < blocks.size() - 1; i++){
        colision = blocks[i].colisionWithBlock(blocks[blocks.size() - 1], std::pair<int,int>(0, 0)); if(colision) break;
      }
      if(!colision) colision = blocks[blocks.size() - 1].colisionX(ROWS);
      if(!colision) colision = blocks[blocks.size() - 1].colisionY(COLUMNS);
      if(colision) blocks[blocks.size() - 1].rotate(1);
    }
    if(event.key.keysym.sym == SDLK_q){
      blocks[blocks.size() - 1].rotate(1);
      bool colision = false;
      for(int i = 0; i < blocks.size() - 1; i++){
        colision = blocks[i].colisionWithBlock(blocks[blocks.size() - 1], std::pair<int,int>(0, 0)); if(colision) break;
      }
      if(!colision) colision = blocks[blocks.size() - 1].colisionX(ROWS);
      if(!colision) colision = blocks[blocks.size() - 1].colisionY(COLUMNS);
      if(colision) blocks[blocks.size() - 1].rotate(-1);
    }
    if(event.key.keysym.sym == SDLK_ESCAPE) running = false;
    break;
  }
}

Block::Block(Window *window, Uint8 x, Uint8 y, std::initializer_list<std::pair<int, int>> blocks)
  : window(window), x(x), y(y), blocks(blocks) {}

void Block::render(SDL_Rect canva){
  for(std::pair<int, int> &el : blocks)
    window->renderFillSquare((x + el.first) * CELLSIZE + canva.x, canva.y + (y + el.second)*CELLSIZE, CELLSIZE, CELLSIZE, colour.r, colour.g, colour.b);
}

bool Block::colisionX(int x) {
  bool colision = false;
  for(std::pair<int,int> &el : blocks){
      if(this->x + el.first == x || static_cast<int>(this->x) + static_cast<int>(el.first) < 0) colision = true;
      if(colision) break;
    }
  return colision;
}

bool Block::colisionY(int y) {
  bool colision = false;
  for(std::pair<int,int> &el : blocks){
    if(this->y + el.second == y || static_cast<int>(this->y) + static_cast<int>(el.second) < 0) colision = true;
    if(colision) break;
  }
    
  return colision;
}

void Block::removeY(int y) {
  for(std::pair<int,int> &el : blocks){
    if(this->y + el.second == y ||  static_cast<int>(this->y) + static_cast<int>(el.second) < 0) {el.first = 0; el.second = 0;}
  }
}

bool Block::colision(Uint8 x, Uint8 y) {
  bool colision = false;
  for(std::pair<int,int> &el : blocks)
    if(this->x + el.first == x && this->y + el.second == y) colision = true;
  return colision;
}

bool Block::colisionWithBlock(Block block, std::pair<int,int> move) {
  bool colision = false;
  for (std::pair<int,int> &el : block.blocks){
    colision = this->colision(block.x + el.first + move.first, block.y + el.second + move.second);
    if (colision) return colision;
  }
  return colision;
}

void Block::rotate(int rotation) {
  if(rotation == -1){
    for(std::pair<int,int> &el : blocks){
      int first = el.first;
      el.first = 0 - el.second;
      el.second = first;
    }
  }
  else if(rotation == 1){
    for(std::pair<int,int> &el : blocks){
      int second = el.second;
      el.second = 0 - el.first;
      el.first = second;
    }
  }
}
