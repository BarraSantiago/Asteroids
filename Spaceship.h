#pragma once
#include <raylib.h>

struct Spaceship
{
    Rectangle spaceship;
    Vector2 aceleration;
    Vector2 velocity;
    int lives;
    bool isAlive;
    float rotation;
};

Spaceship InitSpaceship();
float RepositionSpaceship(Rectangle spaceship);
void MovePlayer(Spaceship& player, Vector2 mousePos);
void WarpCoords(Spaceship& player);
void DrawSpaceship(Rectangle spaceship, float playerRotation, Texture2D spaceshipTexture);