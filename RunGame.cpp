#include "RunGame.h"
#include <iostream>
#include <vector>
#include "Asteroid.h"
#include "Bullet.h"
#include "MenuScreens/menu.h"
#include "Spaceship.h"
#include "raylib.h"
#include "MenuScreens/MenuEnums.h"

enum class MenuOptions;
using namespace std;

#pragma region functions
void UpdateBullets(Bullet bullets[]);
void UpdateAsteroids(vector<Asteroid>& asteroids, Spaceship spaceship);
void SpawnSpecial(vector<Asteroid>& asteroids);
void UpdateSpaceship(Bullet bullets[], Spaceship& spaceship);
void PowerUp();
void DrawGame(vector<Asteroid> asteroids, Bullet bullets[], Spaceship spaceship, Vector2 mousePos);
void DrawPowerUp();
void DrawShield(Spaceship spaceship);
void CheckBulletAsteroidCollision(vector<Asteroid>& asteroids, Bullet bullets[]);
void CheckAsteroidPlayerCollision(vector<Asteroid> asteroids, Spaceship& spaceship);
void CheckPowerUpPlayerCollision(Spaceship spaceship);
void Update(vector<Asteroid>& asteroids, Bullet bullets[], Spaceship& spaceship);
void CheckWin(vector<Asteroid> asteroids);
void CheckCollisions(vector<Asteroid>& asteroids, Bullet bullets[], Spaceship& spaceship);
bool CircleCircleCollision(Circle c1, Circle c2);
void InitAsteroids(std::vector<Asteroid>& asteroids, int quantity, Circle spaceship);
void LoadResources();
void UnloadResources();
void LoseScreen();
void DrawScore();
void WinScreen();
#pragma endregion

#pragma region globalVariables
extern Texture2D backgroundTexture;
static Texture2D spaceshipTexture;
static Texture2D asteroidsTexture;
static Texture2D specialAsteroidsTexture;
Texture2D bulletTexture;

static Circle powerUp1;

static Sound shooting;
static Sound hit;
static Music backgrounMusic;

static int score;
static float damagedTimer = 0;
static float powerUp1Timer = 7.0f;
static float specialTimer = 5.0f;

extern bool music;
extern bool sound;
extern bool debugMode;
static bool isPowerUp1 = false;
static bool win = false;

extern MenuOptions menuOptions;

#pragma endregion

void RunGame()
{
#pragma region declarations
    InitAudioDevice();
    SetMasterVolume(0.07f);

    LoadResources();

    Bullet bullets[50];
    damagedTimer = 0;
    vector<Asteroid> asteroids;
    win = false;
    isPowerUp1 = false;
    Spaceship player = InitSpaceship();
    Vector2 mousePos = GetMousePosition();
    InitAsteroids(asteroids, 10, player.body);
#pragma endregion
    while (!WindowShouldClose() && player.isAlive && !win)
    {
        mousePos = GetMousePosition();
        CheckCollisions(asteroids, bullets, player);
        Update(asteroids, bullets, player);
        DrawGame(asteroids, bullets, player, mousePos);
    }
    if (!player.isAlive)
    {
        while (!WindowShouldClose())
        {
            LoseScreen();
        }
    }
    else if (win)
    {
        while (!WindowShouldClose())
        {
            WinScreen();
        }
    }

    UnloadResources();
    CloseAudioDevice();
    menuOptions = MenuOptions::menu;
}

void LoseScreen()
{
    constexpr Color AltRed = {230, 41, 55, 80};
    BeginDrawing();
    DrawBackground();
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), AltRed);
    DrawText("You Lost!\nPress Esc to return to menu",
             GetScreenWidth() / 2 - MeasureText("Press Esc to return to menu", GetScreenWidth() / 24) / 2,
             GetScreenHeight() / 3, GetScreenWidth() / 24, BLUE);
    EndDrawing();
}

void WinScreen()
{
    constexpr Color AltBlue = {0, 121, 241, 80};
    BeginDrawing();
    DrawBackground();
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), AltBlue);
    DrawText("You Won!\nPress Esc to return to menu",
             GetScreenWidth() / 2 - MeasureText("Press Esc to return to menu", GetScreenWidth() / 24) / 2,
             GetScreenHeight() / 3, GetScreenWidth() / 24, RED);
    EndDrawing();
}

void LoadResources()
{
    asteroidsTexture = LoadTexture("res/asteroids_asteroids.png");
    specialAsteroidsTexture = LoadTexture("res/asteroids_special.png");
    spaceshipTexture = LoadTexture("res/asteroids_spaceship.png");
    bulletTexture = LoadTexture("res/spaceship_bullet.png");
    if (sound)
    {
        shooting = LoadSound("res/spaceship_shoot.wav");
        hit = LoadSound("res/spaceship_hit.wav");
    }
    if (music)
    {
        backgrounMusic = LoadMusicStream("res/backgroundMusic.wav");
        PlayMusicStream(backgrounMusic);
    }
}

void UnloadResources()
{
    UnloadTexture(spaceshipTexture);
    UnloadTexture(bulletTexture);
    UnloadTexture(asteroidsTexture);
    UnloadTexture(specialAsteroidsTexture);
    UnloadSound(shooting);
    UnloadSound(hit);
}

void InitAsteroids(std::vector<Asteroid>& asteroids, int quantity, Circle spaceship)
{
    float x, y;
    for (int i = 0; i < quantity; ++i)
    {
        x = static_cast<float>(GetRandomValue(-GetScreenWidth() / 20, GetScreenWidth() + GetScreenWidth() / 20));
        y = static_cast<float>(GetRandomValue(-GetScreenHeight() / 20, GetScreenHeight() + GetScreenHeight() / 20));
        if (CircleCircleCollision(spaceship, {x, y, static_cast<float>(GetScreenWidth()) / 10.0f}))
        {
            i--;
            continue;
        }
        asteroids.push_back(InitAsteroid({x, y}, AsteroidSize::Large));
    }
}

void DrawGame(vector<Asteroid> asteroids, Bullet bullets[], Spaceship spaceship, Vector2 mousePos)
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawBackground();
    DrawPowerUp();
    if (debugMode)
    {
        DrawLine(static_cast<int>(mousePos.x), static_cast<int>(mousePos.y), static_cast<int>(spaceship.body.x),
                 static_cast<int>(spaceship.body.y), WHITE);
    }
    DrawBullets(bullets);
    DrawSpaceship(spaceship.body, spaceship.rotation, spaceshipTexture);
    DrawShield(spaceship);
    DrawAsteroids(asteroids, asteroidsTexture, specialAsteroidsTexture);
    DrawLives(spaceshipTexture, spaceship.lives);
    DrawScore();
    EndDrawing();
}

void DrawPowerUp()
{
    constexpr Color altBlue = {0, 121, 241, 130};
    if (isPowerUp1)
    {
        DrawCircle(static_cast<int>(powerUp1.x), static_cast<int>(powerUp1.y), powerUp1.radius, altBlue);
    }
}

void DrawShield(Spaceship spaceship)
{
    constexpr Color altBlue = {0, 121, 241, 130};
    if (damagedTimer > 0)
    {
        DrawCircle(static_cast<int>(spaceship.body.x), static_cast<int>(spaceship.body.y), spaceship.body.radius,
                   altBlue);
    }
}

void DrawScore()
{
    DrawText(TextFormat("Score: %i", score), GetScreenWidth() / 4, 0, GetScreenWidth() / 30, RAYWHITE);
}

void Update(vector<Asteroid>& asteroids, Bullet bullets[], Spaceship& spaceship)
{
    PowerUp();
    UpdateAsteroids(asteroids, spaceship);
    UpdateBullets(bullets);
    UpdateSpaceship(bullets, spaceship);
    CheckWin(asteroids);
    if (music)
    {
        UpdateMusicStream(backgrounMusic);
    }
}

void CheckWin(vector<Asteroid> asteroids)
{
    for (int i = 0; i < static_cast<int>(asteroids.size()); ++i)
    {
        if (asteroids[i].isActive)
        {
            return;
        }
    }
    win = true;
}

void UpdateBullets(Bullet bullets[])
{
    for (int i = 0; i < 5; ++i)
    {
        if (!bullets[i].isActive) continue;

        MoveBullet(bullets[i]);
    }
}

void UpdateAsteroids(vector<Asteroid>& asteroids, Spaceship spaceship)
{
    specialTimer -= GetFrameTime();

    MoveAsteroids(asteroids, {spaceship.body.x, spaceship.body.y});

    if (specialTimer <= 0) SpawnSpecial(asteroids);
}

void SpawnSpecial(vector<Asteroid>& asteroids)
{
    float x = static_cast<float>(GetRandomValue(0, GetScreenWidth()));
    float y = static_cast<float>(GetRandomValue(0, 1));
    y = y == 0 ? 0 : static_cast<float>(GetScreenHeight());
    asteroids.push_back({
        {x, y, static_cast<float>(GetScreenWidth()) / 20.0f}, AsteroidSize::SpecialL, {0, 0}, 130, true
    });
    specialTimer = 8.0f;
}

void UpdateSpaceship(Bullet bullets[], Spaceship& spaceship)
{
    Vector2 mousePos = GetMousePosition();
    spaceship.rotation = RepositionSpaceship(spaceship.body);
    MovePlayer(spaceship, mousePos);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        Shoot(spaceship.body, mousePos, bullets);
        if (sound)
        {
            PlaySound(shooting);
        }
    }
}

void CheckCollisions(vector<Asteroid>& asteroids, Bullet bullets[], Spaceship& spaceship)
{
    CheckBulletAsteroidCollision(asteroids, bullets);
    CheckAsteroidPlayerCollision(asteroids, spaceship);
    CheckPowerUpPlayerCollision(spaceship);
}

void CheckPowerUpPlayerCollision(Spaceship spaceship)
{
    if (CircleCircleCollision(spaceship.body, powerUp1))
    {
        isPowerUp1 = false;
        powerUp1Timer = 13.0f;
        damagedTimer = 4.0f;
    }
}

void CheckBulletAsteroidCollision(vector<Asteroid>& asteroids, Bullet bullets[])
{
    for (int j = 0; j < static_cast<int>(sizeof(bullets)) - 1; ++j)
    {
        for (int i = 0; i < static_cast<int>(asteroids.size()); i++)
        {
            if (!bullets[j].isActive || !asteroids[i].isActive) continue;

            if (!CircleCircleCollision(bullets[j].body, asteroids[i].body)) continue;

            score += static_cast<int>(asteroids[i].size);
            bullets[j].isActive = false;
            SpawnAsteroids(asteroids, i);
        }
    }
}

void CheckAsteroidPlayerCollision(vector<Asteroid> asteroids, Spaceship& spaceship)
{
    if (damagedTimer > 0)
    {
        damagedTimer -= GetFrameTime();
        return;
    }

    for (int i = 0; i < static_cast<int>(asteroids.size()); ++i)
    {
        if (!asteroids[i].isActive) continue;

        if (!CircleCircleCollision(spaceship.body, asteroids[i].body)) continue;

        if (sound)
        {
            PlaySound(hit);
        }

        spaceship.lives--;
        damagedTimer = 1.5f;
        if (spaceship.lives <= 0)
        {
            spaceship.isAlive = false;
        }
    }
}

bool CircleCircleCollision(Circle c1, Circle c2)
{
    const float distX = c1.x - c2.x;
    const float distY = c1.y - c2.y;
    const float distance = sqrt((distX * distX) + (distY * distY));

    return distance <= c1.radius + c2.radius;
}

void PowerUp()
{
    if (powerUp1Timer <= 0 && !isPowerUp1)
    {
        float x = static_cast<float>(GetRandomValue(0, GetScreenWidth()));
        float y = static_cast<float>(GetRandomValue(0, GetScreenHeight()));
        powerUp1 = {x, y, static_cast<float>(GetScreenWidth()) / 35.0f};
        isPowerUp1 = true;
    }
    else
    {
        powerUp1Timer -= GetFrameTime();
    }
}
