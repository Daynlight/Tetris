#pragma once 
#include "../Settings.h"
#include "../Renderer/Renderer.h"
#include <chrono>
#include <random>

struct Block {
  Block(Window * window, Uint8 x = 0, Uint8 y = 0, std::initializer_list<std::pair<int, int>> blocks = {{0, 0}});
  void render(SDL_Rect canva);
  bool colision(Uint8 x, Uint8 y);
  bool colisionWithBlock(Block block, std::pair<int,int> move);
  bool colisionX(int x);
  bool colisionY(int y);
  void removeY(int x);
  void rotate(int rotation);
  std::vector<std::pair<int, int>> blocks;
  SDL_Colour colour = SDL_Colour(0,0,0);
  Uint8 x = 0, y = 0;
  Window * window;
};

class Tetris{
public:
  Tetris(Window* window);
  void run();
  void start();
  bool isRunning();
  void tetrisEvent(SDL_Event event);
private:
  void initBlockVariants();
  void createBlockVariant(std::initializer_list<std::pair<int,int>> list);
  size_t random(size_t x);
  std::vector<Block> blocks;
  std::vector<Block> blocks_variants;
  std::vector<SDL_Colour> colour_variants;
  Window* window;
  bool running = true;
  Uint32 points = 0;
  std::chrono::time_point<std::chrono::high_resolution_clock> last;
};
