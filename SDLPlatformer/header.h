#pragma once

#include <chrono>
#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include "Vector2.h"

using namespace std;
using namespace Biff;

// Global enums
enum class Axis
{
	X = 0,
	Y = 1
};

enum class Direction
{
	UP = 0,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 3
};

enum class GameState
{
	MAIN_MENU = 0,
	GAME = 1,
	PAUSE = 2,
	GAME_OVER = 3
};

enum class PlayerState
{
	SPAWN = -1,
	DEAD = 0,
	IDLE = 1,
	RUN = 2,
	JUMP = 3,
	CROUCH = 4,
	CLIMB = 5,
	GRAPPLE = 6
};

// Global constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

// Global variables

// Global objects
extern SDL_Window* window;
extern SDL_Renderer* renderer;
