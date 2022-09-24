#pragma once
#include <raylib.h>

enum class AsteroidSize
{
    Small,
    Medium,
    Big,
    Special
};

struct Asteroid
{
    Vector2 position;
    Vector2 direction;
    
    float speed;

    AsteroidSize size;

    bool isActive;
};

void InitAsteroid();