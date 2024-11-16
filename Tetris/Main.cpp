#include "Game/Game.h"
#include "Renderer/Renderer.h"
#include "vendor/Data/Data.h"

static const char *TITLE = "Tetris";
static const char SETTINGSPATH[] = "settings";
static const SDL_WindowFlags WINDOWFLAGS = SDL_WindowFlags(SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
static const SDL_Rect WINDOWDEFAULTSIZE(100, 100, 500, 500);

int WinMain(){
  Data::File settings = Data::File(SETTINGSPATH, 4);
  if(settings.isEmpty()){
    settings[0] = std::to_string(WINDOWDEFAULTSIZE.x);
    settings[1] = std::to_string(WINDOWDEFAULTSIZE.y);
    settings[2] = std::to_string(WINDOWDEFAULTSIZE.w);
    settings[3] = std::to_string(WINDOWDEFAULTSIZE.h);
    settings.save();
  }
  else settings.read();

  Window window(TITLE, std::stoi(settings[0]), std::stoi(settings[1]), std::stoi(settings[2]), std::stoi(settings[3]), WINDOWFLAGS);
  App app(&window);
  app.Run();

  SDL_Rect rect = window.GetWindowPositionAndSize();
  settings[0] = std::to_string(rect.x);
  settings[1] = std::to_string(rect.y);
  settings[2] = std::to_string(rect.w);
  settings[3] = std::to_string(rect.h);
  settings.save();

  return 0;
}