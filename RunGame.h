#pragma once
#include <iostream>
#include <string>
#include "raylib.h"

struct Player
{
	Vector2 front;
	Vector2 left;
	Vector2 right;
};

void RunGame();
void DrawGame(Player player);
void DrawPlayer(Player player);
Player InitPlayer();