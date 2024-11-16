#include "Game/Game.h"
#include "Renderer/Renderer.h"

static const char *TITLE = "Tetris";
static const char SETTINGSPATH[] = "settings";
static const SDL_WindowFlags WINDOWFLAGS = SDL_WindowFlags(
  SDL_WINDOW_SHOWN | 
  SDL_WINDOW_RESIZABLE);

int WinMain(){
  Window window(TITLE, 500, 500, 500, 500, WINDOWFLAGS);
  App app(&window);
  app.Run();

  return 0;
}