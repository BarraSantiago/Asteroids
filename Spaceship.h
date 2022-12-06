#pragma once
#include <raylib.h>

#include "Circle.h"
namespace barra
{
    struct Spaceship
    {
        Circle body;
        Vector2 aceleration;
        int lives;
        bool isAlive;
        float rotation;
    };

    Spaceship InitSpaceship();
    float RepositionSpaceship(Circle body);
    void MovePlayer(Spaceship& player, Vector2 mousePos);
    void WarpCoords(Spaceship& player);
    void DrawSpaceship(Circle body, float rotation, Texture2D spaceshipTexture);
    void DrawShield(Spaceship spaceship);
    void DrawLives( Texture2D spaceshipTexture, int lives);
}