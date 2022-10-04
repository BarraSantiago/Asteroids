#pragma once
#include <raylib.h>

enum class AsteroidSize
{
    Small,
    Medium,
    Big,
    Special
};

struct Circle
{
    float x;
    float y;
    float radius;
    Color color;
};

struct Asteroid
{
    Circle position;
    AsteroidSize size;
    Vector2 direction;
    float speed;
    bool isActive;
};

Asteroid InitBigAsteroid();
Asteroid InitMediumAsteroid();
void DrawAsteroid(Asteroid asteroid);
void SpawnBigAsteroids(Asteroid asteroids[], int quantity);
void WarpAsteroid(Asteroid& asteroid);