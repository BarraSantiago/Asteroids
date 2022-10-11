#pragma once
#include <raylib.h>
#include <vector>
#include "Circle.h"

enum class AsteroidSize
{
    Small,
    Medium,
    Large,
    Special
};

struct Asteroid
{
    Circle body;
    AsteroidSize size;
    Vector2 direction;
    float speed;
    bool isActive;
};


void DrawAsteroids(std::vector<Asteroid> asteroids, Texture2D texture);
void SpawnBigAsteroids(std::vector<Asteroid>& asteroids, int quantity);
void WarpAsteroid(Asteroid& asteroid);
void SpawnAsteroid(std::vector<Asteroid>& asteroids, int vecPosition);
