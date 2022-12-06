#include "Asteroid.h"
#include <raymath.h>

#include "DrawAdapted.h"
#include "MenuEnums.h"


static float rotation = 0;

namespace barra
{
    extern bool debugMode;
    void DrawAsteroid(Asteroid asteroid, Texture2D texture);

    float CalculateRadius(AsteroidSize size)
    {
        switch (size)
        {
        case AsteroidSize::Small:
        case AsteroidSize::SpecialS:
            return static_cast<float>(GetScreenWidth()) / 75.0f;
            break;
        case AsteroidSize::Medium:
        case AsteroidSize::SpecialM:
            return static_cast<float>(GetScreenWidth()) / 40.0f;
            break;
        case AsteroidSize::Large:
        case AsteroidSize::SpecialL:
            return static_cast<float>(GetScreenWidth()) / 20.0f;
            break;
        default:
            break;
        }
        return static_cast<float>(GetScreenWidth()) / 10.0f;
    }

    Asteroid InitAsteroid(Vector2 position, AsteroidSize size)
    {
        float speed;
        float radius = CalculateRadius(size);
        switch (size)
        {
        case AsteroidSize::Small:
        case AsteroidSize::SpecialS:
            speed = 150.0f;
            break;
        case AsteroidSize::Medium:
        case AsteroidSize::SpecialM:
            speed = 200.0f;
            break;
        case AsteroidSize::Large:
        case AsteroidSize::SpecialL:
            speed = 75;
            break;
        default:
            speed = 30.0f;
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
        for (Asteroid asteroid : asteroids)
        {
            if (asteroid.isActive)
            {
                DrawAsteroid(asteroid, asteroid.size < AsteroidSize::SpecialS ? texture : special);
            }
        }
    }


    void DrawAsteroid(Asteroid asteroid, Texture2D texture)
    {
        const Rectangle sourceRec = TextureToSourceRec(texture);
        const Rectangle position = {
            asteroid.body.x, asteroid.body.y, asteroid.body.radius * 2, asteroid.body.radius * 2
        };
        const Vector2 origin = {asteroid.body.radius, asteroid.body.radius};

        DrawTexturePro(texture, sourceRec, position, origin, rotation, RAYWHITE);

        if (debugMode)
        {
            DrawCircleLines(static_cast<int>(asteroid.body.x), static_cast<int>(asteroid.body.y), asteroid.body.radius,
                            WHITE);
        }
        rotation += GetFrameTime();
    }

    void SpawnAsteroid(std::vector<Asteroid>& asteroids, int vecPosition, AsteroidSize size)
    {
        const Vector2 mapPosition = {asteroids[vecPosition].body.x, asteroids[vecPosition].body.y};
        int quantity = 2;

        switch (size)
        {
        case AsteroidSize::Small:
        case AsteroidSize::SpecialS:
            quantity = 0;
            break;
        case AsteroidSize::SpecialM:
        case AsteroidSize::SpecialL:
            quantity = 1;
            break;
        case AsteroidSize::Medium:
        case AsteroidSize::Large:
            quantity = 2;
            break;
        }

        asteroids.erase(asteroids.begin() + vecPosition);
        size = static_cast<AsteroidSize>(static_cast<int>(size) - 1);

        for (int i = 0; i < quantity; ++i)
        {
            asteroids.push_back(InitAsteroid(mapPosition, size));
        }
    }

    void SpawnAsteroids(std::vector<Asteroid>& asteroids, int vecPosition)
    {
        AsteroidSize size = asteroids[vecPosition].size;

        SpawnAsteroid(asteroids, vecPosition, size);
    }

    void MoveAsteroid(Asteroid& asteroid)
    {
        Vector2 velocity = {
            GetFrameTime() * asteroid.direction.x * asteroid.speed,
            GetFrameTime() * asteroid.direction.y * asteroid.speed
        };
        asteroid.body.x += velocity.x;
        asteroid.body.y += velocity.y;
        WarpAsteroid(asteroid);
    }

    void MoveAsteroids(std::vector<Asteroid>& asteroids, Vector2 spaceshipPos)
    {
        for (Asteroid& asteroid : asteroids)
        {
            if (!asteroid.isActive) continue;

            if (asteroid.size >= AsteroidSize::SpecialS)
            {
                asteroid.direction = {
                    spaceshipPos.x - asteroid.body.x, spaceshipPos.y - asteroid.body.y
                };
                asteroid.direction = Vector2Normalize(asteroid.direction);
            }

            MoveAsteroid(asteroid);
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
}
