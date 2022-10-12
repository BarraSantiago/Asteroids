#include "RunGame.h"
#include <iostream>
#include <vector>
#include "Asteroid.h"
#include "Bullet.h"
#include "raylib.h"
#include "Spaceship.h"

using namespace std;

#pragma region functions
void UpdateBullets(Bullet bullets[]);
void UpdateAsteroids(vector<Asteroid>& asteroids);
void UpdateSpaceship( Bullet bullets[], Spaceship& spaceship);
void DrawGame(vector<Asteroid> asteroids, Bullet bullets[], Spaceship spaceship, Vector2 mousePos);
void CheckBulletAsteroidCollision(vector<Asteroid>& asteroids, Bullet bullets[] );
void CheckAsteroidPlayerCollision(vector<Asteroid> asteroids, Spaceship& spaceship);
void Update(vector<Asteroid>& asteroids, Bullet bullets[], Spaceship& spaceship);
void CheckCollisions(vector<Asteroid>& asteroids, Bullet bullets[], Spaceship& spaceship);
bool CircleCircleCollision(Circle c1, Circle c2);
void SpawnBigAsteroids(std::vector<Asteroid>& asteroids, int quantity, Circle spaceship);
#pragma endregion

#pragma region globalVariables
static Texture2D spaceshipTexture;
Texture2D bulletTexture;
static Texture2D asteroidsTexture;
static Sound shooting;
static Sound hit;
static float damagedTimer;
#pragma endregion

void RunGame()
{
    
#pragma region declarations
    InitAudioDevice();
    SetMasterVolume(0.07f);
    
    asteroidsTexture = LoadTexture("res/asteroids_asteroids.png");
    spaceshipTexture = LoadTexture("res/asteroids_spaceship.png");
    bulletTexture = LoadTexture("res/spaceship_bullet.png");
    shooting =  LoadSound("res/spaceship_shoot.wav");
    hit =  LoadSound("res/spaceship_hit.wav");

    const Music backgrounMusic = LoadMusicStream("res/backgroundMusic.wav");
    PlayMusicStream(backgrounMusic);
    
    Bullet bullets[9];

    vector<Asteroid> asteroids;

    Spaceship player = InitSpaceship();

    SpawnBigAsteroids(asteroids, 10, player.body);
    
    Vector2 mousePos {};

#pragma endregion

    while (!WindowShouldClose())// && player.isAlive)
    {
        UpdateMusicStream(backgrounMusic);
        mousePos = GetMousePosition();
        CheckCollisions(asteroids, bullets, player);
        Update(asteroids, bullets, player);
        DrawGame( asteroids, bullets, player, mousePos);
    }
    if(!player.isAlive)
    {
        //DEAD SCREEN
    }
    UnloadTexture(spaceshipTexture);
    UnloadTexture(bulletTexture);
    UnloadTexture(asteroidsTexture);
    UnloadSound(shooting);
    UnloadSound(hit);
    CloseAudioDevice();
    CloseWindow();
}

void SpawnBigAsteroids(std::vector<Asteroid>& asteroids, int quantity, Circle spaceship)
{
    float x, y;
    for (int i = 0; i < quantity; ++i)
    {
        x = static_cast<float>(GetRandomValue(-GetScreenWidth() / 20,GetScreenWidth() + GetScreenWidth() / 20));
        y = static_cast<float>(GetRandomValue(-GetScreenHeight() / 20,GetScreenHeight() + GetScreenHeight() / 20));
        if(CircleCircleCollision(spaceship,{x,y,static_cast<float>(GetScreenWidth()) / 10.0f}))
        {
            i--;
            continue;
        } 
            asteroids.push_back(InitAsteroid({x, y}, AsteroidSize::Large));
    }
}

void DrawGame( vector<Asteroid> asteroids, Bullet bullets[], Spaceship spaceship, Vector2 mousePos)
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawLine(static_cast<int>(mousePos.x), static_cast<int>(mousePos.y), static_cast<int>(spaceship.body.x),
             static_cast<int>(spaceship.body.y), WHITE);
    DrawBullets(bullets);
    DrawSpaceship(spaceship.body, spaceship.rotation, spaceshipTexture);
    DrawAsteroids(asteroids, asteroidsTexture);
    EndDrawing();
}

void Update(vector<Asteroid>& asteroids, Bullet bullets[], Spaceship& spaceship)
{
    UpdateAsteroids(asteroids);
    UpdateBullets(bullets);
    UpdateSpaceship(bullets, spaceship);
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

void UpdateSpaceship(Bullet bullets[], Spaceship& spaceship)
{
    Vector2 mousePos = GetMousePosition();
    spaceship.rotation = RepositionSpaceship(spaceship.body);
    MovePlayer(spaceship, mousePos);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Shoot(spaceship.body, mousePos, bullets);
        PlaySound(shooting);
    }
}

void CheckCollisions( vector<Asteroid>& asteroids, Bullet bullets[], Spaceship& spaceship)
{
    CheckBulletAsteroidCollision( asteroids, bullets);
    CheckAsteroidPlayerCollision(asteroids, spaceship);
}

void CheckBulletAsteroidCollision( vector<Asteroid>& asteroids, Bullet bullets[])
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

void CheckAsteroidPlayerCollision(vector<Asteroid> asteroids, Spaceship& spaceship)
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
                    PlaySound(hit);
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
