#include "RunGame.h"

#include "Spaceship.h"

using namespace std;

void RunGame()
{
    int width = 720;
    int height = 480;

    float playerRotation = 0.01f;

    Bullet bullets[5];

    InitWindow(width, height, "Asteroids");

    Vector2 mousePos = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
    Spaceship player = InitSpaceship();

    while (!WindowShouldClose())
    {
        
        mousePos = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            Shoot(player.spaceShip, mousePos, bullets);

        playerRotation = RepositionSpaceship(player.spaceShip);
        UpdateObjects(bullets);
        MovePlayer(player.spaceShip, mousePos);
        DrawGame(player.spaceShip, playerRotation, mousePos, bullets);
    }
    CloseWindow();
}


void UpdateObjects(Bullet bullets[])
{
    for (int i = 0; i < sizeof(bullets); ++i)
    {
        if (bullets[i].isActive)
        {
            bullets[i].position.x += (bullets[i].speed * bullets[i].direction.x) * GetFrameTime() * 400.0f;
            bullets[i].position.y += (bullets[i].speed * bullets[i].direction.y) * GetFrameTime() * 400.0f;
            bullets[i].isActive = bullets[i].position.x > 0 && bullets[i].position.x < GetScreenWidth() && bullets[i].
                position.y > 0 && bullets[i].position.y < GetScreenHeight();
        }
    }
}

void DrawGame(Rectangle player, float playerRotation, Vector2 mousePos, Bullet bullets[])
{
    BeginDrawing();
    ClearBackground(BLACK);

    DrawLine(mousePos.x, mousePos.y, player.x, player.y, WHITE);
    DrawBullets(bullets);
    DrawSpaceship(player, playerRotation);

    EndDrawing();
}
