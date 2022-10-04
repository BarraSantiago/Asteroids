#include "Asteroid.h"
#include <raymath.h>

Asteroid InitBigAsteroid()
{
    float positionX = static_cast<float>(GetRandomValue(-GetScreenWidth() / 20,  GetScreenWidth()+ GetScreenWidth() / 20));
    float positionY = static_cast<float>(GetRandomValue(-GetScreenWidth() / 20, GetScreenHeight()+ GetScreenWidth() / 20));
    
    float radius = GetScreenWidth() / 20.0f;
    
    Circle body = {positionX, positionY, radius, WHITE};
    
    Vector2 direction;
    direction.x = static_cast<float>(GetRandomValue(-70, 70));
    direction.y = static_cast<float>(GetRandomValue(-70, 70));
    direction.x += static_cast<int>(direction.x) >= 0 ? 10 : -10;
    direction.y += static_cast<int>(direction.y) >= 0 ? 10 : -10;
    direction = Vector2Normalize(direction);
    Vector2 speed;
    speed.x = 75;
    speed.y = 75;

    AsteroidSize asteroidSize = AsteroidSize::Big;

    bool isActive = true;
    return {body, asteroidSize, direction, speed.x, isActive};
}

Asteroid InitMediumAsteroid()
{
    float positionX = static_cast<float>(GetRandomValue(-GetScreenWidth() / 50, GetScreenWidth()));
    float positionY = static_cast<float>(GetRandomValue(-GetScreenHeight() / 50, GetScreenHeight()));

    Circle body = {positionX, positionY, GetScreenWidth() / 20.0f, GREEN};
    Vector2 direction = {};

    float speed = 200.0f;

    AsteroidSize asteroidSize = AsteroidSize::Big;

    bool isActive = true;

    return {body, asteroidSize, {direction.x, direction.y}, speed, isActive};
}

void DrawAsteroid(Asteroid asteroid)
{
    DrawCircle(static_cast<int>(asteroid.position.x), static_cast<int>(asteroid.position.y), asteroid.position.radius,WHITE);
}

void SpawnBigAsteroids(Asteroid asteroids[], int quantity)
{
    for (int i = 0; i < quantity; ++i)
    {
        asteroids[i] = InitBigAsteroid();
    }
}

void WarpAsteroid(Asteroid& asteroid)
{
    if (asteroid.position.x < 0) 
    {
        asteroid.position.x += GetScreenWidth();
    }
    if (asteroid.position.x > GetScreenWidth())
    {
        asteroid.position.x -= GetScreenWidth();
    }
    if (asteroid.position.y < 0)
    {                 
        asteroid.position.y += GetScreenHeight();
    }                 
    if (asteroid.position.y > GetScreenHeight())
    {                 
        asteroid.position.y -= GetScreenHeight();
    }
}