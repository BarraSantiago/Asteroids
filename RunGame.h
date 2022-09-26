#pragma once
#include <iostream>
#include <string>
#include <math.h>
#include "raylib.h"
#include "Bullet.h"

struct Asteroid;
void RunGame();
void DrawGame(Rectangle player, float playerRotation, Vector2 mousePos, Bullet bullets[], Texture2D spaceshipTexture, Asteroid asteroids[]);
void UpdateObjects(Bullet bullets[], Asteroid asteroids[]);

