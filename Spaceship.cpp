#include "Spaceship.h"
#include <cmath>
#include "raymath.h"

void AcelerationLimitator(float& aceleration)
{
    if (aceleration>0.35f)
    {
        aceleration = 0.35f;
    }
    else if(aceleration < -0.35f)
    {
        aceleration = -0.35f;
    }
}

void MovePlayer(Spaceship& player, Vector2 mousePos)
{
    Vector2 direcVector = {mousePos.x - player.body.x, mousePos.y - player.body.y};
    Vector2 normVector = Vector2Normalize(direcVector);

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        player.aceleration.x += normVector.x*GetFrameTime() / 6.0f;
        player.aceleration.y += normVector.y*GetFrameTime() / 6.0f;
        AcelerationLimitator(player.aceleration.x);
        AcelerationLimitator(player.aceleration.y);
    }
    player.body.x += player.aceleration.x;
    player.body.y += player.aceleration.y;

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
    
    if(player.body.y > static_cast<float>(GetScreenHeight()))
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

void DrawLives( Texture2D spaceshipTexture, int lives)
{
    const int frameWidth = spaceshipTexture.width;
    const int frameHeight = spaceshipTexture.height;
    const Rectangle sourceRec = { 0.0f, 0.0f, static_cast<float>(frameWidth), static_cast<float>(frameHeight) };
    constexpr Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
    const Vector2 origin = {0,0};
    for (int i = 0; i < lives; ++i)
    {
    DrawTexturePro(spaceshipTexture, sourceRec, {10 + static_cast<float>(frameWidth)/8*i,0, frameWidth/7.0f, frameHeight/7.0f}, origin, 0, NEONCYAN);
    }
}

void DrawSpaceship(Circle body, float rotation, Texture2D spaceshipTexture)
{
    const int frameWidth = spaceshipTexture.width;
    const int frameHeight = spaceshipTexture.height;
    const Rectangle sourceRec = { 0.0f, 0.0f, static_cast<float>(frameWidth), static_cast<float>(frameHeight) };
    constexpr Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
    const Vector2 origin = {body.radius , body.radius};
    
    DrawTexturePro(spaceshipTexture, sourceRec, {body.x, body.y, body.radius*2, body.radius*2}, origin, rotation+90, NEONCYAN);
    extern bool debugMode;
    if(debugMode)
    {
        DrawCircleLines(static_cast<int>(body.x), static_cast<int>(body.y), body.radius, NEONCYAN);
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
