#pragma once
#include <iostream>
#include <string>
#include <math.h>
#include "raylib.h"

void RunGame();
void DrawGame(Rectangle player, float playerRotation);
void DrawPlayer(Rectangle Player, float playerRotation);
float RepositionPlayer(Rectangle player);
Rectangle InitPlayer();