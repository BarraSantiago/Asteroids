#include "RunGame.h"
#include <iostream>
#include <vector>
#include "Asteroid.h"
#include "Bullet.h"
#include "raylib.h"
#include "Spaceship.h"

using namespace std;

#pragma region functionDec
void UpdateBullets(Bullet bullets[]);
void UpdateAsteroids(vector<Asteroid>& asteroids);
void DrawGame(Circle player, float playerRotation, Vector2 mousePos, Bullet bullets[], Texture2D spaceshipTexture,
              vector<Asteroid> asteroids);
void CheckBulletAsteroidCollision(Bullet bullets[], vector<Asteroid>& asteroids);
void CheckAsteroidPlayerCollision(Spaceship& spaceship, vector<Asteroid> asteroids);
void UpdateObjects(Bullet bullets[], vector<Asteroid>& asteroids);
void CheckCollisions(Bullet bullets[], vector<Asteroid>& asteroids);
bool CircleCircleCollision(Circle c1, Circle c2);
#pragma endregion


void RunGame()
{
    int width = 1080;
    int height = 920;
    InitWindow(width, height, "Asteroids");

#pragma region declarations
    Bullet bullets[5];

    vector<Asteroid> asteroids;

    SpawnBigAsteroids(asteroids, 2);

    Spaceship player = InitSpaceship();
    Texture2D spaceshipTexture = LoadTexture("res/asteroids_spaceship.png");

    Vector2 mousePos = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
#pragma endregion

    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Shoot(player.body, mousePos, bullets);
        }

        mousePos = GetMousePosition();
        player.rotation = RepositionSpaceship(player.body);
        CheckCollisions(bullets, asteroids);
        UpdateObjects(bullets, asteroids);
        MovePlayer(player, mousePos);
        DrawGame(player.body, player.rotation, mousePos, bullets, spaceshipTexture, asteroids);
    }

    UnloadTexture(spaceshipTexture);
    CloseWindow();
}

void DrawGame(Circle player, float playerRotation, Vector2 mousePos, Bullet bullets[], Texture2D spaceshipTexture,
              vector<Asteroid> asteroids)
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawLine(static_cast<int>(mousePos.x), static_cast<int>(mousePos.y), static_cast<int>(player.x),
             static_cast<int>(player.y), WHITE);
    DrawBullets(bullets);
    DrawSpaceship(player, playerRotation, spaceshipTexture);
    DrawAsteroids(asteroids);
    EndDrawing();
}

void UpdateObjects(Bullet bullets[], vector<Asteroid>& asteroids)
{
    UpdateAsteroids(asteroids);
    UpdateBullets(bullets);
}

void UpdateBullets(Bullet bullets[])
{
    for (int i = 0; i < 5; ++i)
    {
        if (bullets[i].isActive)
        {
            bullets[i].body.x += bullets[i].speed * bullets[i].direction.x * GetFrameTime();
            bullets[i].body.y += bullets[i].speed * bullets[i].direction.y * GetFrameTime();
            bullets[i].isActive = 0 < bullets[i].body.x && bullets[i].body.x < static_cast<float>(GetScreenWidth()) && 0
                < bullets[
                    i].body.y && bullets[i].body.y < static_cast<float>(GetScreenHeight());
        }
    }
}

void UpdateAsteroids(vector<Asteroid>& asteroids)
{
    for (int i = 0; i < static_cast<int>(asteroids.size()); ++i)
    {
        if (asteroids[i].isActive)
        {
            Vector2 velocity = {
                GetFrameTime() * asteroids[i].direction.x * asteroids[i].speed,
                GetFrameTime() * asteroids[i].direction.y * asteroids[i].speed
            };
            asteroids[i].body.x += velocity.x;
            asteroids[i].body.y += velocity.y;
            WarpAsteroid(asteroids[i]);
        }
    }
}

void CheckCollisions(Bullet bullets[], vector<Asteroid>& asteroids)
{
    CheckBulletAsteroidCollision(bullets, asteroids);
    //CheckAsteroidPlayerCollision();
}

void CheckBulletAsteroidCollision(Bullet bullets[], vector<Asteroid>& asteroids)
{
    for (int j = 0; j < static_cast<int>(sizeof(bullets)) - 1; ++j)
    {
        for (int i = 0; i < static_cast<int>(asteroids.size()); i++)
        {
            if (bullets[j].isActive && asteroids[i].isActive)
            {
                if (CircleCircleCollision(bullets[j].body, asteroids[i].body))
                {
                    bullets[j].isActive = false;
                    SpawnAsteroid(asteroids, i);
                }
            }
        }
    }
}

bool CircleCircleCollision(Circle c1, Circle c2)
{
    float distX = c1.x - c2.x;
    float distY = c1.y - c2.y;
    float distance = sqrt((distX * distX) + (distY * distY));

    // if the distance is less than the sum of the circle's
    // radii, the circles are touching!
    return distance <= c1.radius + c2.radius;
}

void CheckAsteroidPlayerCollision(Spaceship spaceship, vector<Asteroid> asteroids)
{
    spaceship.lives--;
}
