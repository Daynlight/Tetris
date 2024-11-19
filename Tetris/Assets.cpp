#include "Game/Tetris.h"

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