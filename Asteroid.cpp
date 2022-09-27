#include "Asteroid.h"
#include <raymath.h>

Asteroid InitBigAsteroid()
{
    float positionX = GetRandomValue(-(GetScreenWidth() / 20.0f), GetScreenWidth()+ GetScreenWidth() / 20.0f);
    float positionY = GetRandomValue(-(GetScreenWidth() / 20.0f), GetScreenHeight()+ GetScreenWidth() / 20.0f);
    
    float radius = GetScreenWidth() / 20.0f;
    
    Circle body = {positionX, positionY, radius, WHITE};
    
    Vector2 direction;
    direction.x = GetRandomValue(-70, 70);
    direction.y = GetRandomValue(-70, 70);
    direction.x += direction.x > 0 ? 10 : -10;
    direction.y += direction.y > 0 ? 10 : -10;
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
    int positionX = GetRandomValue(-(GetScreenWidth() / 50), GetScreenWidth());
    int positionY = GetRandomValue(-(GetScreenHeight() / 50), GetScreenHeight());

    Circle body = {positionX, positionY, GetScreenWidth() / 20.0f, GREEN};
    Vector2 direction = {};

    float speed = 200.0f;

    AsteroidSize asteroidSize = AsteroidSize::Big;

    bool isActive = true;

    return {body, asteroidSize, {direction.x, direction.y}, speed, isActive};
}

void DrawAsteroid(Asteroid asteroid)
{
    DrawCircle(asteroid.body.x, asteroid.body.y, asteroid.body.radius,WHITE);
}

void SpawnBigAsteroids(Asteroid asteroids[], int quantity)
{
    for (int i = 0; i < quantity; ++i)
    {
        asteroids[i] = InitBigAsteroid();
    }
}
