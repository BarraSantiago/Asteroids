#pragma once
#include <iostream>
#include <string>
#include <math.h>
#include "raylib.h"
#include "Bullet.h"

void RunGame();
void DrawGame(Rectangle player, float playerRotation, Vector2 mousePos, Bullet bullets[]);
void DrawSpaceship(Rectangle Player, float playerRotation);
void UpdateObjects(Bullet bullets[]);

