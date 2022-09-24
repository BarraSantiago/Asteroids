#pragma once
#include <raylib.h>

struct Spaceship
{
    Rectangle spaceShip;
    float aceleration;
    int lives;
    bool isAlive;
    
};

Spaceship InitSpaceship();
float RepositionSpaceship(Rectangle spaceship);
void MovePlayer(Rectangle& player, Vector2 mousePos);