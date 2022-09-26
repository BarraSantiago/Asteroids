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
    int x;
    int y;
    float radius;
    Color color;
};
struct Asteroid
{
    Circle body;
    AsteroidSize size;
    Vector2 direction;
    float speed;
    bool isActive;
};

Asteroid InitBigAsteroid();
Asteroid InitMediumAsteroid();
void DrawAsteroid(Asteroid asteroid);