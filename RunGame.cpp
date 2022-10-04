﻿#include "RunGame.h"

#include "Asteroid.h"
#include "Spaceship.h"

using namespace std;

void UpdateBullets(Bullet bullets[]);
void UpdateAsteroids(Asteroid asteroids[]);

void RunGame()
{
    int width = 1080;
    int height = 920;

    InitWindow(width, height, "Asteroids");
    
    Bullet bullets[5];
    
    Asteroid bigAsteroids[5];
    SpawnBigAsteroids(bigAsteroids, 5);
    
    Spaceship player = InitSpaceship();
    Texture2D spaceshipTexture = LoadTexture("src/asteroids_spaceship.png");
    
    Vector2 mousePos = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};

    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            Shoot(player.spaceship, mousePos, bullets);

        mousePos = GetMousePosition();
        player.rotation = RepositionSpaceship(player.spaceship);
        UpdateObjects(bullets, bigAsteroids);
        MovePlayer(player, mousePos);
        DrawGame(player.spaceship, player.rotation, mousePos, bullets, spaceshipTexture, bigAsteroids);
    }
    UnloadTexture(spaceshipTexture);
    CloseWindow();
}


void UpdateObjects(Bullet bullets[], Asteroid asteroids[])
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
            bullets[i].position.x += bullets[i].speed * bullets[i].direction.x * GetFrameTime();
            bullets[i].position.y += bullets[i].speed * bullets[i].direction.y * GetFrameTime();
            bullets[i].isActive = 0 < bullets[i].position.x && bullets[i].position.x  < GetScreenWidth() && 0 < bullets[i].position.y && bullets[i].position.x < GetScreenHeight();
        }
    }
}

void UpdateAsteroids(Asteroid asteroids[])
{
    int max = sizeof(asteroids);
    for (int i = 0; i < max; ++i)
    {
        if (asteroids[i].isActive)
        {
            Vector2 velocity = { GetFrameTime() * asteroids[i].direction.x * asteroids[i].speed, GetFrameTime() * asteroids[i].direction.y * asteroids[i].speed };
            asteroids[i].body.x += velocity.x;
            asteroids[i].body.y += velocity.y;
            WarpAsteroid(asteroids[i]);
        }
    }
}


void DrawGame(Rectangle player, float playerRotation, Vector2 mousePos, Bullet bullets[], Texture2D spaceshipTexture, Asteroid asteroids[])
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawLine(static_cast<int>(mousePos.x), static_cast<int>(mousePos.y), static_cast<int>(player.x), static_cast<int>(player.y), WHITE);
    DrawBullets(bullets);
    DrawSpaceship(player, playerRotation, spaceshipTexture);
    for (int i = 0; i < 5; ++i)
    {
        DrawAsteroid(asteroids[i]);
    }
    EndDrawing();
}
