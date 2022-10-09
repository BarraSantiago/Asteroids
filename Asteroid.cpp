#include "Asteroid.h"
#include <raymath.h>
#include <algorithm>

void DrawAsteroid(Asteroid asteroid);
Asteroid InitBigAst();
Asteroid InitMediumAst(Vector2 position);
Asteroid InitSmallAst(Vector2 position);

Asteroid InitBigAst()
{
    float speed = 75;
    
    float positionX = static_cast<float>(GetRandomValue(-GetScreenWidth() / 20,
                                                        GetScreenWidth() + GetScreenWidth() / 20));
    float positionY = static_cast<float>(GetRandomValue(-GetScreenWidth() / 20,
                                                        GetScreenHeight() + GetScreenWidth() / 20));

    float radius = GetScreenWidth() / 20.0f;

    Circle body = {positionX, positionY, radius, WHITE};

    Vector2 direction;
    direction.x = static_cast<float>(GetRandomValue(-70, 70));
    direction.x += static_cast<int>(direction.x) >= 0 ? 10 : -10;
    direction.y = static_cast<float>(GetRandomValue(-70, 70));
    direction.y += static_cast<int>(direction.y) >= 0 ? 10 : -10;
    direction = Vector2Normalize(direction);
    
    
    
    return {body, AsteroidSize::Big, direction, speed, true};
}

Asteroid InitMediumAst(Vector2 position)
{
    float speed = 200.0f;
    
    Circle body = {position.x, position.y, GetScreenWidth() / 40.0f, GREEN};

    Vector2 direction;
    direction.x = static_cast<float>(GetRandomValue(-70, 70));
    direction.x += static_cast<int>(direction.x) >= 0 ? 10 : -10;
    direction.y = static_cast<float>(GetRandomValue(-70, 70));
    direction.y += static_cast<int>(direction.y) >= 0 ? 10 : -10;
    direction = Vector2Normalize(direction);

    return {body, AsteroidSize::Medium, direction, speed, true};
}

Asteroid InitSmallAst(Vector2 position)
{
    float speed = 150.0f;
    Circle body = {position.x, position.y, GetScreenWidth() / 75.0f, GREEN};

    Vector2 direction;
    direction.x = static_cast<float>(GetRandomValue(-70, 70));
    direction.x += static_cast<int>(direction.x) >= 0 ? 10 : -10;
    direction.y = static_cast<float>(GetRandomValue(-70, 70));
    direction.y += static_cast<int>(direction.y) >= 0 ? 10 : -10;
    direction = Vector2Normalize(direction);

    return {body, AsteroidSize::Small, direction, speed, true};
}

void DrawAsteroids(std::vector<Asteroid> asteroids)
{
    for (int i = 0; i < static_cast<int>(asteroids.size()) - 1; ++i)
    {
        if (asteroids[i].isActive)
        {
            DrawAsteroid(asteroids[i]);
        }
    }
}

void DrawAsteroid(Asteroid asteroid)
{
    DrawCircle(static_cast<int>(asteroid.position.x), static_cast<int>(asteroid.position.y), asteroid.position.radius,
               WHITE);
}

void SpawnBigAsteroids(std::vector<Asteroid>& asteroids, int quantity)
{
    for (int i = 0; i < quantity; ++i)
    {
        asteroids.push_back(InitBigAst());
    }
}

void SpawnAsteroid(std::vector<Asteroid>& asteroids, int vecPosition)
{
    Vector2 mapPosition = {asteroids[vecPosition].position.x,asteroids[vecPosition].position.y};
    
    switch (asteroids[vecPosition].size)
    {
    case AsteroidSize::Small:
        asteroids[vecPosition].isActive = false;
        break;
    case AsteroidSize::Medium:
        asteroids[vecPosition] = InitSmallAst(mapPosition);
        asteroids.push_back(InitSmallAst(mapPosition));
        break;
    case AsteroidSize::Big:
        asteroids[vecPosition] = InitMediumAst(mapPosition);
        asteroids.push_back(InitMediumAst(mapPosition));
        break;
    case AsteroidSize::Special:
        break;
    default:
        break;
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
