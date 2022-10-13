#include "Asteroid.h"
#include <raymath.h>


void DrawAsteroid(Asteroid asteroid, Texture2D texture);

static float rotation = 0;
extern bool debugMode;

Asteroid InitSpecialAsteroid(Vector2 position,  AsteroidSize size)
{

    float speed = 30.0f;
    float radius = static_cast<float>(GetScreenWidth()) / 10.0f;
    switch (size)
    {
    case AsteroidSize::SpecialS:
        speed = 170.0f;
        radius = static_cast<float>(GetScreenWidth()) / 75.0f;
        break;
    case AsteroidSize::SpecialM:
        speed = 190.0f;
        radius = static_cast<float>(GetScreenWidth()) / 40.0f;
        break;
    case AsteroidSize::SpecialL:
        speed = 200.0f;
        radius = static_cast<float>(GetScreenWidth()) / 20.0f;
        break;
    default: ;
    }
    
    Circle body = {position.x, position.y, radius};
    
    return {body, size, {0,0}, speed, true};
}
Asteroid InitAsteroid(Vector2 position,  AsteroidSize size)
{
    float speed = 30.0f;
    float radius = static_cast<float>(GetScreenWidth()) / 10.0f;
    switch (size)
    {
    case AsteroidSize::Small:
        speed = 150.0f;
        radius = static_cast<float>(GetScreenWidth()) / 75.0f;
        break;
    case AsteroidSize::Medium:
        speed = 200.0f;
        radius = static_cast<float>(GetScreenWidth()) / 40.0f;
        break;
    case AsteroidSize::Large:
        speed = 75;
        radius = static_cast<float>(GetScreenWidth()) / 20.0f;
        break;
    default:
        radius = static_cast<float>(GetScreenWidth()) / 10.0f;
        break;

    }
    Circle body = {position.x, position.y, radius};
    Vector2 direction;
    direction.x = static_cast<float>(GetRandomValue(-70, 70));
    direction.x += static_cast<int>(direction.x) >= 0 ? 10 : -10;
    direction.y = static_cast<float>(GetRandomValue(-70, 70));
    direction.y += static_cast<int>(direction.y) >= 0 ? 10 : -10;
    direction = Vector2Normalize(direction);

    return {body, size, direction, speed, true};
}

void DrawAsteroids(std::vector<Asteroid> asteroids, Texture2D texture, Texture2D special)
{
    for (int i = 0; i < static_cast<int>(asteroids.size()); ++i)
    {
        if (asteroids[i].isActive)
        {
            DrawAsteroid(asteroids[i], asteroids[i].size < AsteroidSize::SpecialS ? texture : special);
        }
    }
}

void DrawAsteroid(Asteroid asteroid, Texture2D texture)
{
    const float frameWidth = static_cast<float>(texture.width);
    const float frameHeight = static_cast<float>(texture.height);
    const Rectangle sourceRec = { 0,0,frameWidth,frameHeight};
    const Vector2 origin = {asteroid.body.radius , asteroid.body.radius};
    
    DrawTexturePro(texture, sourceRec, {asteroid.body.x, asteroid.body.y, asteroid.body.radius*2, asteroid.body.radius*2}, origin, rotation, RAYWHITE);
    if(debugMode)
    {
        DrawCircleLines(static_cast<int>(asteroid.body.x), static_cast<int>(asteroid.body.y), asteroid.body.radius, WHITE);
    }
    rotation += 1*GetFrameTime();
}

void SpawnAsteroid(std::vector<Asteroid>& asteroids, int vecPosition)
{
    const Vector2 mapPosition = {asteroids[vecPosition].body.x, asteroids[vecPosition].body.y};
    const AsteroidSize size = asteroids[vecPosition].size;

    switch (size)
    {
    case AsteroidSize::Small:
        asteroids[vecPosition].isActive = false;
        break;
    case AsteroidSize::Medium:

        asteroids[vecPosition] = InitAsteroid(mapPosition, AsteroidSize::Small);
        asteroids.push_back(InitAsteroid(mapPosition, AsteroidSize::Small));
        break;
    case AsteroidSize::Large:
        asteroids[vecPosition] = InitAsteroid(mapPosition, AsteroidSize::Medium);
        asteroids.push_back(InitAsteroid(mapPosition, AsteroidSize::Medium));
        break;
    case AsteroidSize::SpecialS:
        asteroids[vecPosition].isActive = false;
        break;
    case AsteroidSize::SpecialM:
        asteroids[vecPosition] = InitSpecialAsteroid(mapPosition, AsteroidSize::SpecialS);
        break;
    case AsteroidSize::SpecialL:
        asteroids[vecPosition] = InitSpecialAsteroid(mapPosition, AsteroidSize::SpecialM);
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
