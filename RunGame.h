#pragma once
#include <iostream>
#include <string>
#include <math.h>
#include "raylib.h"

void RunGame();
void DrawGame(Rectangle player);
void DrawPlayer(Rectangle Player);
float RepositionPlayer(Rectangle player);
Rectangle InitPlayer();