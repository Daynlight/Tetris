#include "Game/Game.h"
#include "Settings.h"
#include "Renderer/Renderer.h"
#include "vendor/Data/Data.h"

int WinMain(){
  // Read Files
  Data::File settings = Data::File(SETTINGSPATH, 4);
  if(settings.isEmpty()){
    settings[0] = std::to_string(WINDOWDEFAULTSIZE.x);
    settings[1] = std::to_string(WINDOWDEFAULTSIZE.y);
    settings[2] = std::to_string(WINDOWDEFAULTSIZE.w);
    settings[3] = std::to_string(WINDOWDEFAULTSIZE.h);
    settings.save();
  } else settings.read();

  Data::File leaderboard = Data::File(LEADERBOARDPATH, 1);
  if(leaderboard.isEmpty()){
    leaderboard[0] = std::to_string(0);
    leaderboard.save();
  } else leaderboard.read();

  // Run App
  Window window(std::stoi(settings[0]), std::stoi(settings[1]), std::stoi(settings[2]), std::stoi(settings[3]));
  App app(&window, &leaderboard);
  app.run();

  // Save Window
  SDL_Rect rect = window.getWindowPositionAndSize();
  settings[0] = std::to_string(rect.x);
  settings[1] = std::to_string(rect.y);
  settings[2] = std::to_string(rect.w);
  settings[3] = std::to_string(rect.h);
  settings.save();

  return 0;
}