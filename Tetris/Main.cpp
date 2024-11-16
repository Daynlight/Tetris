#include "Game/Game.h"
#include "Renderer/Renderer.h"

static const char *TITLE = "Tetris";
static const char SETTINGSPATH[] = "settings";

int WinMain(){
  Window window(TITLE, 500, 500, 500, 500, SDL_WINDOW_SHOWN);
  App app(&window);

  return 0;
}