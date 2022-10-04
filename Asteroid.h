#pragma once
#include <raylib.h>
#include <vector>

enum class AsteroidSize
{
    Small,
    Medium,
    Big,
    Special
};

struct Circle
{
    float x;
    float y;
    float radius;
    Color color;
};

struct Asteroid
{
    Circle position;
    AsteroidSize size;
    Vector2 direction;
    float speed;
    bool isActive;
};

Asteroid InitBigAsteroid();
Asteroid InitMediumAsteroid();
void DrawAsteroids(std::vector<Asteroid> asteroids);
void SpawnBigAsteroids(std::vector<Asteroid>& asteroids, int quantity);
void WarpAsteroid(Asteroid& asteroid);
void SpawnAsteroid(std::vector<Asteroid> asteroids, int positionOrigin);
