#pragma once
#include <SDL.h>

static const char TITLE[] = "Tetris";
static const char SETTINGSPATH[] = "settings";
static const char LEADERBOARDPATH[] = "leaderboard";
static const SDL_WindowFlags WINDOWFLAGS = SDL_WindowFlags(SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
static const SDL_Rect WINDOWDEFAULTSIZE(100, 100, 500, 500);
static const Uint8 COLUMNS = 15, ROWS = 11;
static const Uint32 CELLSIZE = 30, TICKSPEED = 1000;