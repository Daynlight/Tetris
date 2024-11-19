#include "Tetris.h"

Tetris::Tetris(Window* window)
  :window(window) {
  initBlockVariants();
  start();
}

void Tetris::initBlockVariants() {
  blocks_variants.reserve(7);
  colour_variants.reserve(5);
  createBlockVariant({{0,0}, {0,1}, {1,0}, {1,1}});
  createBlockVariant({{0,0}, {0,1}, {0,2}, {0,3}});
  createBlockVariant({{0,0}, {1,0}, {0,1}, {-1,1}});
  createBlockVariant({{0,0}, {-1,0}, {0,1}, {1,1}});
  createBlockVariant({{0,0}, {0,1}, {0,2}, {1,2}});
  createBlockVariant({{0,0}, {0,1}, {0,2}, {-1,2}});
  createBlockVariant({{0,0}, {1,0}, {-1,0}, {0,1}});
  colour_variants.emplace_back(3, 65, 174);
  colour_variants.emplace_back(114, 203, 59);
  colour_variants.emplace_back(255, 213, 0);
  colour_variants.emplace_back(255, 151, 28);
  colour_variants.emplace_back(255, 50, 19);
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
      blocks.emplace_back(blocks_variants[random(blocks_variants.size() - 1)]);
      blocks[blocks.size() - 1].colour = colour_variants[random(colour_variants.size() - 1)];
    }
    last = std::chrono::high_resolution_clock::now();
  }
}

void Tetris::start(){
  blocks.clear();
  blocks.emplace_back(blocks_variants[random(blocks_variants.size() - 1)]);
  blocks[blocks.size() - 1].colour = colour_variants[random(colour_variants.size() - 1)];
  running = true;
  last = std::chrono::high_resolution_clock::now();
}

bool Tetris::isRunning(){ return running; }

void Tetris::tetrisEvent(SDL_Event event){
  switch (event.type){
  case SDL_KEYDOWN:
    if(event.key.keysym.sym == SDLK_LEFT && !blocks[blocks.size() - 1].colisionX(0)){
      bool colision = false;
      for(int i = 0; i < blocks.size() - 1; i++){
        colision = blocks[i].colisionWithBlock(blocks[blocks.size() - 1], std::pair<int,int>(-1, 0)); if(colision) break;
        colision = blocks[i].colisionWithBlock(blocks[blocks.size() - 1], std::pair<int,int>(0, 1)); if(colision) break;
        colision = blocks[blocks.size() - 1].colisionY(COLUMNS - 1); if(colision) break;
      }
      if(!colision) blocks[blocks.size() -1].x--;
    }
    if(event.key.keysym.sym == SDLK_RIGHT && !blocks[blocks.size() - 1].colisionX(ROWS - 1)) {
      bool colision = false;
      for(int i = 0; i < blocks.size() - 1; i++){
        colision = blocks[i].colisionWithBlock(blocks[blocks.size() - 1], std::pair<int,int>(1, 0)); if(colision) break;
        colision = blocks[i].colisionWithBlock(blocks[blocks.size() - 1], std::pair<int,int>(0, 1)); if(colision) break;
        colision = blocks[blocks.size() - 1].colisionY(COLUMNS - 1); if(colision) break;
      }
      if(!colision) blocks[blocks.size() -1].x++;
    }
    if(event.key.keysym.sym == SDLK_DOWN && !blocks[blocks.size() - 1].colisionY(COLUMNS - 1)) {
      bool colision = false;
      for(int i = 0; i < blocks.size() - 1; i++){
        colision = blocks[i].colisionWithBlock(blocks[blocks.size() - 1], std::pair<int,int>(0, 1)); if(colision) break;
        colision = blocks[blocks.size() - 1].colisionY(COLUMNS - 1); if(colision) break;
        last = std::chrono::high_resolution_clock::now();
      }
      if(!colision) blocks[blocks.size() -1].y++;
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

bool Block::colisionX(Uint8 x) {
  bool colision = false;
  for(std::pair<int,int> &el : blocks){
      if(this->x + el.first == x) colision = true;
      if(colision) break;
    }
  return colision;
}

bool Block::colisionY(Uint8 y) {
  bool colision = false;
  for(std::pair<int,int> &el : blocks){
    if(this->y + el.second == y) colision = true;
    if(colision) break;
  }
    
  return colision;
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

void Block::rotate(Uint8 rotation) {
}
