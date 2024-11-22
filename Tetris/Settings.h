#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

static const char TITLE[] = "Tetris";
static const char SETTINGSPATH[] = "settings";
static const char LEADERBOARDPATH[] = "leaderboard";
static const SDL_WindowFlags WINDOWFLAGS = SDL_WindowFlags(SDL_WINDOW_SHOWN);
static const Uint8 COLUMNS = 15, ROWS = 11;
static const SDL_Rect WINDOWDEFAULTSIZE(100, 100, 30*ROWS, 30*COLUMNS + 70);
static const Uint32 CELLSIZE = 30, TICKSPEED = 700;
static const float COMBOMULTIPLYER = 1.5f;
static const Uint32 BASEPOINTSFORROW = 1000;
static const std::string FONTNAME = "Minecraft.ttf";
static const Uint32 FONTSIZE = 64;