#pragma once
#include <raylib.h>

struct Spaceship
{
    Rectangle spaceShip;
    Vector2 aceleration;
    Vector2 velocity;
    int lives;
    bool isAlive;
    
};

Spaceship InitSpaceship();
float RepositionSpaceship(Rectangle spaceship);
void MovePlayer(Spaceship& player, Vector2 mousePos);