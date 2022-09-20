#pragma once
#include <iostream>
#include <string>
#include <math.h>
#include "raylib.h"

void RunGame();
void DrawGame(Rectangle player, float playerRotation, Vector2 mousePos);
void DrawPlayer(Rectangle Player, float playerRotation);
float RepositionPlayer(Rectangle player);
void MovePlayer(Rectangle& player, Vector2 mousePos);
Rectangle InitPlayer();