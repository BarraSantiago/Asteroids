#include "Spaceship.h"
#include <cmath>
#include "raymath.h"

void AcelerationLimitator(float& aceleration)
{
    float maxSpeed = .35f;
    if (aceleration > maxSpeed)
    {
        aceleration = maxSpeed;
    }
    else if (aceleration < -maxSpeed)
    {
        aceleration = -maxSpeed;
    }
}

void PlayerAceleration(Vector2& aceleration, Vector2 mousePos, Vector2 playerPos)
{
    constexpr float playerSpeed = 300.f;
    
    Vector2 direcVector = {mousePos.x - playerPos.x, mousePos.y - playerPos.y};
    Vector2 normVector = Vector2Normalize(direcVector);
    
    aceleration.x += normVector.x * GetFrameTime() * playerSpeed;
    aceleration.y += normVector.y * GetFrameTime() * playerSpeed;
}

void MovePlayer(Spaceship& player, Vector2 mousePos)
{
    Vector2 playerPos{player.body.x, player.body.y};
    
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        PlayerAceleration(player.aceleration, mousePos, playerPos);
    }
    
    player.body.x += player.aceleration.x * GetFrameTime();
    player.body.y += player.aceleration.y * GetFrameTime();

    WarpCoords(player);
}

void WarpCoords(Spaceship& player)
{
    if (player.body.x < 0)
        player.body.x += static_cast<float>(GetScreenWidth());

    if (player.body.y < 0)
        player.body.y += static_cast<float>(GetScreenHeight());

    if (player.body.x > static_cast<float>(GetScreenWidth()))
        player.body.x -= static_cast<float>(GetScreenWidth());

    if (player.body.y > static_cast<float>(GetScreenHeight()))
        player.body.y -= static_cast<float>(GetScreenHeight());
}


float RepositionSpaceship(Circle body)
{
    Vector2 direcVector = {static_cast<float>(GetMouseX()) - body.x, static_cast<float>(GetMouseY()) - body.y};

    float angle = atan(direcVector.y / direcVector.x);

    angle *= 180 / acos(-1.0f); //CONVERSION RAD TO DEG

    if (direcVector.x < 0)
    {
        angle += 180;
    }

    return angle;
}

Rectangle TextureToSourceRec(Texture2D texture)
{
    int frameWidth = texture.width;
    int frameHeight = texture.height;
    return {0.0f, 0.0f, static_cast<float>(frameWidth), static_cast<float>(frameHeight)};
}

void DrawTextureCyan(Texture2D texture, Rectangle position, Vector2 origin, float rotation)
{
    constexpr Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
    Rectangle sourceRec = TextureToSourceRec(texture);
    DrawTexturePro(texture, sourceRec, position, origin, rotation, NEONCYAN);
}

void DrawLives(Texture2D spaceshipTexture, int lives)
{
    float textureWidth = static_cast<float>(spaceshipTexture.width);
    float textureHeight = static_cast<float>(spaceshipTexture.height);
    const Vector2 origin = {0, 0};

    for (int i = 0; i < lives; ++i)
    {
        Rectangle position = {
            10 + textureWidth / 8 * i, 0, textureWidth / 7.0f, textureHeight / 7.0f
        };
        DrawTextureCyan(spaceshipTexture, position, origin, 0);
    }
}

void DrawSpaceship(Circle body, float rotation, Texture2D spaceshipTexture)
{
    const Vector2 origin = {body.radius, body.radius};
    Rectangle position = {body.x, body.y, body.radius * 2, body.radius * 2};
    DrawTextureCyan(spaceshipTexture, position, origin, rotation + 90);

    extern bool debugMode;
    if (debugMode)
    {
        DrawCircleLines(static_cast<int>(body.x), static_cast<int>(body.y), body.radius, {4, 217, 255, 255});
    }
}

Spaceship InitSpaceship()
{
    Circle body{};
    body.x = static_cast<float>(GetScreenWidth()) / 2.0f;
    body.y = static_cast<float>(GetScreenHeight()) / 2.0f;
    body.radius = static_cast<float>(GetScreenWidth()) / 30.0f;
    constexpr float aceleration = 0;
    constexpr int lives = 3;
    constexpr bool isAlive = true;
    return {body, {aceleration, aceleration}, lives, isAlive};
}
