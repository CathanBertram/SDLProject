#pragma once
#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Timer.h"

using namespace std;

//Screen Dimensions
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 416

#define MAP_WIDTH 16
#define MAP_HEIGHT 13

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

#define SCREENSHAKE_DURATION 0.25f

#define INJURED_TIME 2.5f

#define INITIAL_JUMP_FORCE_SMALL 400.0f

#define KOOPA_SPEED 96.0f
#endif