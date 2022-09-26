#include "RunGame.h"

#include "Spaceship.h"

using namespace std;

void RunGame()
{
    int width = 1080;
    int height = 920;

    Bullet bullets[5];

    InitWindow(width, height, "Asteroids");
    Texture2D spaceshipTexture = LoadTexture("src/asteroids_spaceship.png");
    Vector2 mousePos = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    Spaceship player = InitSpaceship();

    while (!WindowShouldClose())
    {
        
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            Shoot(player.spaceship, mousePos, bullets);

        mousePos = GetMousePosition();
        player.rotation = RepositionSpaceship(player.spaceship);
        UpdateObjects(bullets);
        MovePlayer(player, mousePos);
        DrawGame(player.spaceship, player.rotation, mousePos, bullets, spaceshipTexture);
    }
    UnloadTexture(spaceshipTexture);
    CloseWindow();
}


void UpdateObjects(Bullet bullets[])
{
    for (int i = 0; i < 5; ++i)
    {
        if (bullets[i].isActive)
        {
            bullets[i].position.x += (bullets[i].speed * bullets[i].direction.x) * GetFrameTime();
            bullets[i].position.y += (bullets[i].speed * bullets[i].direction.y) * GetFrameTime();
            bullets[i].isActive = 0 < bullets[i].position.x < GetScreenWidth() &&  0 < bullets[i].position.y < GetScreenHeight();
        }
    }
}

void DrawGame(Rectangle player, float playerRotation, Vector2 mousePos, Bullet bullets[], Texture2D spaceshipTexture)
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawLine(mousePos.x, mousePos.y, player.x, player.y, WHITE);
    DrawBullets(bullets);
    DrawSpaceship(player, playerRotation, spaceshipTexture);
    EndDrawing();
}
