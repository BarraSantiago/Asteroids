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
void DrawGame(Circle player, float playerRotation, Vector2 mousePos, Bullet bullets[], vector<Asteroid> asteroids, Texture2D astTexture, Texture2D spaTexture);
void CheckBulletAsteroidCollision(Bullet bullets[], vector<Asteroid>& asteroids);
void CheckAsteroidPlayerCollision(Spaceship& spaceship, vector<Asteroid> asteroids);
void UpdateObjects(Bullet bullets[], vector<Asteroid>& asteroids);
void CheckCollisions(Bullet bullets[], vector<Asteroid>& asteroids, Spaceship& spaceship);
bool CircleCircleCollision(Circle c1, Circle c2);
#pragma endregion

static float damagedTimer;
void RunGame()
{
    
#pragma region declarations
    const Texture2D spaceshipTexture = LoadTexture("res/asteroids_spaceship.png");
    const Texture2D asteroidsTexture = LoadTexture("res/asteroids_asteroids.png");
    InitAudioDevice();
    Sound shooting =  LoadSound("res/spaceship_shoot.wav");
    Bullet bullets[9];

    vector<Asteroid> asteroids;

    SpawnBigAsteroids(asteroids, 10);

    Spaceship player = InitSpaceship();
    
    Vector2 mousePos {};

#pragma endregion

    while (!WindowShouldClose())// && player.isAlive)
    {
        mousePos = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Shoot(player.body, mousePos, bullets);
            PlaySound(shooting);
        }
        player.rotation = RepositionSpaceship(player.body);
        CheckCollisions(bullets, asteroids, player);
        UpdateObjects(bullets, asteroids);
        MovePlayer(player, mousePos);
        DrawGame(player.body, player.rotation, mousePos, bullets, asteroids, asteroidsTexture, spaceshipTexture);
    }
    if(!player.isAlive)
    {
        //DEAD SCREEN
    }
    UnloadTexture(spaceshipTexture);
    UnloadTexture(asteroidsTexture);
    UnloadSound(shooting);
    CloseAudioDevice();
    CloseWindow();
}

void DrawGame(Circle player, float playerRotation, Vector2 mousePos, Bullet bullets[], vector<Asteroid> asteroids, Texture2D astTexture, Texture2D spaTexture)
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawLine(static_cast<int>(mousePos.x), static_cast<int>(mousePos.y), static_cast<int>(player.x),
             static_cast<int>(player.y), WHITE);
    DrawBullets(bullets);
    DrawSpaceship(player, playerRotation, spaTexture);
    DrawAsteroids(asteroids, astTexture);
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
                < bullets[i].body.y && bullets[i].body.y < static_cast<float>(GetScreenHeight());
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

void CheckCollisions(Bullet bullets[], vector<Asteroid>& asteroids, Spaceship& spaceship)
{
    CheckBulletAsteroidCollision(bullets, asteroids);
    CheckAsteroidPlayerCollision(spaceship, asteroids);
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

void CheckAsteroidPlayerCollision(Spaceship& spaceship, vector<Asteroid> asteroids)
{
    if (damagedTimer<=0)
    {
        for (int i = 0; i < static_cast<int>(asteroids.size()); ++i)
        {
            if (asteroids[i].isActive)
            {
                if (CircleCircleCollision(spaceship.body, asteroids[i].body))
                {
                    spaceship.lives--;
                    damagedTimer = 1.5f;
                    if (spaceship.lives <= 0)
                    {
                        spaceship.isAlive = false;
                    }
                }
            }
        }
    }
    else
    {
        damagedTimer-=GetFrameTime();
    }
}

bool CircleCircleCollision(Circle c1, Circle c2)
{
    const float distX = c1.x - c2.x;
    const float distY = c1.y - c2.y;
    const float distance = sqrt((distX * distX) + (distY * distY));
    
    return distance <= c1.radius + c2.radius;
}
