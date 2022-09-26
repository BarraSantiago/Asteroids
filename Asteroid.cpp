#include "Asteroid.h"


Asteroid InitBigAsteroid()
{
    int positionX = GetRandomValue(-GetScreenWidth()/30,GetScreenWidth());
    int positionY = GetRandomValue(-GetScreenHeight()/30,GetScreenHeight());

    Circle body = {positionX, positionY, GetScreenWidth()/20.0f, WHITE};
    Vector2 direction = {};

    float speed = 200.0f;

    AsteroidSize asteroidSize = AsteroidSize::Big;

    bool isActive = true;
    return {body, asteroidSize, {direction.x, direction.y}, speed, isActive};
}

Asteroid InitMediumAsteroid()
{
    int positionX = GetRandomValue(-GetScreenWidth()/30,GetScreenWidth());
    int positionY = GetRandomValue(-GetScreenHeight()/30,GetScreenHeight());

    Circle asteroid = {positionX, positionY, GetScreenWidth()/20.0f, WHITE};
    Vector2 direction = {};

    float speed = 200.0f;

    AsteroidSize asteroidSize = AsteroidSize::Big;

    bool isActive = true;
    
    return {asteroid, asteroidSize, {direction.x, direction.y}, speed, isActive};
}

void DrawAsteroid(Asteroid asteroid)
{
    DrawCircle(asteroid.body.x, asteroid.body.x, asteroid.body.radius,WHITE);
}

