#include "Asteroid.h"
#include <raymath.h>

void DrawAsteroid(Asteroid asteroid);

Asteroid InitAsteroid(Vector2 position, float speed, float radius, AsteroidSize size)
{
    Circle body = {position.x, position.y, radius};

    Vector2 direction;
    direction.x = static_cast<float>(GetRandomValue(-70, 70));
    direction.x += static_cast<int>(direction.x) >= 0 ? 10 : -10;
    direction.y = static_cast<float>(GetRandomValue(-70, 70));
    direction.y += static_cast<int>(direction.y) >= 0 ? 10 : -10;
    direction = Vector2Normalize(direction);

    return {body, size, direction, speed, true};
}

void DrawAsteroids(std::vector<Asteroid> asteroids)
{
    for (int i = 0; i < static_cast<int>(asteroids.size()); ++i)
    {
        if (asteroids[i].isActive)
        {
            DrawAsteroid(asteroids[i]);
        }
    }
}

void DrawAsteroid(Asteroid asteroid)
{
    DrawCircle(static_cast<int>(asteroid.body.x), static_cast<int>(asteroid.body.y), asteroid.body.radius, WHITE);
}

void SpawnBigAsteroids(std::vector<Asteroid>& asteroids, int quantity)
{
    for (int i = 0; i < quantity; ++i)
    {
        float speed = 75;
        float radius = static_cast<float>(GetScreenWidth()) / 20.0f;

        float positionX = static_cast<float>(GetRandomValue(-GetScreenWidth() / 20,
                                                            GetScreenWidth() + GetScreenWidth() / 20));
        float positionY = static_cast<float>(GetRandomValue(-GetScreenWidth() / 20,
                                                            GetScreenHeight() + GetScreenWidth() / 20));
        asteroids.push_back(InitAsteroid({positionX, positionY},speed,radius,AsteroidSize::Large));
    }
}

void SpawnAsteroid(std::vector<Asteroid>& asteroids, int vecPosition)
{
    
    const float radiusSmall = static_cast<float>(GetScreenWidth()) / 75.0f;
    const float speedSmall = 150.0f;
    
    const float radiusMed = static_cast<float>(GetScreenWidth()) / 40.0f;
    const float speedMed = 200.0f;

    const Vector2 mapPosition = {asteroids[vecPosition].body.x, asteroids[vecPosition].body.y};
    const AsteroidSize size = asteroids[vecPosition].size;
    
    switch (size)
    {
    case AsteroidSize::Small:
        asteroids[vecPosition].isActive = false;
        break;
    case AsteroidSize::Medium:
        
        asteroids[vecPosition] = InitAsteroid(mapPosition, speedSmall, radiusSmall, AsteroidSize::Small);
        asteroids.push_back(InitAsteroid(mapPosition, speedSmall, radiusSmall, AsteroidSize::Small));
        break;
    case AsteroidSize::Large:
        asteroids[vecPosition] = InitAsteroid(mapPosition, speedMed, radiusMed,AsteroidSize::Medium );
        asteroids.push_back(InitAsteroid(mapPosition, speedMed, radiusMed,AsteroidSize::Medium ));
        break;
    case AsteroidSize::Special:
        break;
    default:
        break; 
    }
}

void WarpAsteroid(Asteroid& asteroid)
{
    if (asteroid.body.x < 0)
    {
        asteroid.body.x += static_cast<float>(GetScreenWidth());
    }
    if (asteroid.body.x > static_cast<float>(GetScreenWidth()))
    {
        asteroid.body.x -= static_cast<float>(GetScreenWidth());
    }
    if (asteroid.body.y < 0)
    {
        asteroid.body.y += static_cast<float>(GetScreenHeight());
    }
    if (asteroid.body.y > static_cast<float>(GetScreenHeight()))
    {
        asteroid.body.y -= static_cast<float>(GetScreenHeight());
    }
}
