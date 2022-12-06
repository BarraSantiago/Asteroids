#pragma once
#include <raylib.h>
#include <vector>
#include "Circle.h"
namespace barra
{
    enum class AsteroidSize
    {
        Small,
        Medium,
        Large,
        SpecialS,
        SpecialM,
        SpecialL
    };

    struct Asteroid
    {
        Circle body;
        AsteroidSize size;
        Vector2 direction;
        float speed;
        bool isActive;
    };


    void DrawAsteroids(std::vector<Asteroid> asteroids, Texture2D texture, Texture2D special);
    Asteroid InitAsteroid(Vector2 position,  AsteroidSize size);
    void MoveAsteroids(std::vector<Asteroid>& asteroids, Vector2 spaceshipPos);
    void WarpAsteroid(Asteroid& asteroid);
    void SpawnAsteroids(std::vector<Asteroid>& asteroids, int vecPosition);
}