#pragma once

#include <iostream>
#include <ctime>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#include <SDL.h>

#include "engine/gameWindow.h"
#include "engine/logger.h"
#include "engine/keyboard.h"
#include "engine/mouse.h"
#include "engine/resourceLoader.h"
#include "engine/font.h"
#include "engine/audio.h"
#include "engine/physics.h"
#include "engine/animatedSprite.h"
#include "engine/graphics.h"

#include "gameObject/player.h"
#include "gameObject/miniEnemy.h"
#include "gameObject/bullet.h"
#include "gameObject/powerUp.h"

#define MOUSE_RIGHT 0
#define MOUSE_MIDDLE 1
#define MOUSE_RIGHT 2

#define LIVES 1
#define SHIELD 2
