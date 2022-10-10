#include "Asteroid.h"
#include <raymath.h>

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

    float radius = static_cast<float>(GetScreenWidth()) / 20.0f;

    Circle body = {positionX, positionY, radius, WHITE};

    Vector2 direction;
    direction.x = static_cast<float>(GetRandomValue(-70, 70));
    direction.x += static_cast<int>(direction.x) >= 0 ? 10 : -10;
    direction.y = static_cast<float>(GetRandomValue(-70, 70));
    direction.y += static_cast<int>(direction.y) >= 0 ? 10 : -10;
    direction = Vector2Normalize(direction);

    return {body, AsteroidSize::Large, direction, speed, true};
}
Asteroid InitAsteroid(Vector2 position, float speed, float radius, AsteroidSize size)
{
    Circle body = {position.x, position.y, radius, GREEN};

    Vector2 direction;
    direction.x = static_cast<float>(GetRandomValue(-70, 70));
    direction.x += static_cast<int>(direction.x) >= 0 ? 10 : -10;
    direction.y = static_cast<float>(GetRandomValue(-70, 70));
    direction.y += static_cast<int>(direction.y) >= 0 ? 10 : -10;
    direction = Vector2Normalize(direction);

    return {body, size, direction, speed, true};
}
Asteroid InitMediumAst(Vector2 position)
{
    float speed = 200.0f;

    Circle body = {position.x, position.y, static_cast<float>(GetScreenWidth()) / 40.0f, GREEN};

    Vector2 direction;
    direction.x = static_cast<float>(GetRandomValue(-70, 70));
    direction.x += static_cast<int>(direction.x) >= 0 ? 10 : -10;
    direction.y = static_cast<float>(GetRandomValue(-70, 70));
    direction.y += static_cast<int>(direction.y) >= 0 ? 10 : -10;
    direction = Vector2Normalize(direction);

    return {body, AsteroidSize::Medium, direction, speed, true};
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
    DrawCircle(static_cast<int>(asteroid.position.x), static_cast<int>(asteroid.position.y), asteroid.position.radius,
               asteroid.position.color);
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
    const Vector2 mapPosition = {asteroids[vecPosition].position.x, asteroids[vecPosition].position.y};
    const AsteroidSize size = asteroids[vecPosition].size;
    switch (size)
    {
    case AsteroidSize::Small:
        asteroids[vecPosition].isActive = false;
        break;
    case AsteroidSize::Medium:
        asteroids[vecPosition].isActive = false;
        //asteroids.push_back(InitSmallAst(mapPosition));
        asteroids.push_back(InitAsteroid(mapPosition, 150.0f, static_cast<float>(GetScreenWidth()) / 75.0f, AsteroidSize::Small));
        break;
    case AsteroidSize::Large:
        asteroids[vecPosition].isActive = false;
    //asteroids.push_back(InitMediumAst(mapPosition));
        asteroids.push_back(InitAsteroid(mapPosition, 200.0f,static_cast<float>(GetScreenWidth()) / 40.0f,AsteroidSize::Medium ));
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
        asteroid.position.x += static_cast<float>(GetScreenWidth());
    }
    if (asteroid.position.x > static_cast<float>(GetScreenWidth()))
    {
        asteroid.position.x -= static_cast<float>(GetScreenWidth());
    }
    if (asteroid.position.y < 0)
    {
        asteroid.position.y += static_cast<float>(GetScreenHeight());
    }
    if (asteroid.position.y > static_cast<float>(GetScreenHeight()))
    {
        asteroid.position.y -= static_cast<float>(GetScreenHeight());
    }
}
