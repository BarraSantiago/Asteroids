#include "Asteroid.h"


Asteroid InitBigAsteroid()
{
    int positionX = GetRandomValue(-(GetScreenWidth()/50), GetScreenWidth());
    int positionY = GetRandomValue(-(GetScreenHeight()/50), GetScreenHeight());
    
    float radius = GetScreenWidth() / 20.0f;
    
    Circle body = {positionX, positionY, radius, WHITE};
    
    int directionX = GetRandomValue(-(GetScreenWidth()/50), GetScreenWidth());
    Vector2 direction = {static_cast<float>(positionX), static_cast<float>(positionY)};

    float speed = 200.0f;

    AsteroidSize asteroidSize = AsteroidSize::Big;

    bool isActive = true;
    return {body, asteroidSize, {direction.x, direction.y}, speed, isActive};
}

Asteroid InitMediumAsteroid()
{
    int positionX = GetRandomValue(0, 1080);
    int positionY = GetRandomValue(0, 920);

    Circle body = {positionX, positionY, GetScreenWidth() / 20.0f, WHITE};
    Vector2 direction = {};

    float speed = 200.0f;

    AsteroidSize asteroidSize = AsteroidSize::Big;

    bool isActive = true;

    return {body, asteroidSize, {direction.x, direction.y}, speed, isActive};
}

void DrawAsteroid(Asteroid asteroid)
{
    DrawCircle(asteroid.body.x, asteroid.body.x, asteroid.body.radius,WHITE);
}

void SpawnBigAsteroids(Asteroid asteroids[], int quantity)
{
    for (int i = 0; i < quantity; ++i)
    {
        asteroids[i] = InitBigAsteroid();
    }
}
