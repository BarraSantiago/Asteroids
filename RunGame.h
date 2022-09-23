#pragma once
#include <iostream>
#include <string>
#include <math.h>
#include "raylib.h"

struct Bullet
{
    Vector2 position;
    Vector2 direction;
    
    float speed;

    int size;

    bool isAlive;
};

void RunGame();
void DrawGame(Rectangle player, float playerRotation, Vector2 mousePos, Bullet bullets[]);
void DrawPlayer(Rectangle Player, float playerRotation);
float RepositionPlayer(Rectangle player);
void MovePlayer(Rectangle& player, Vector2 mousePos);
Rectangle InitPlayer();
void Shoot(Rectangle player, Vector2 mousePos, Bullet bullets[]);
void DrawBullets(Bullet bullets[]);