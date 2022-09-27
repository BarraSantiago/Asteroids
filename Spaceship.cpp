#include "Spaceship.h"
#include <cmath>
#include "raymath.h"


void MovePlayer(Spaceship& player, Vector2 mousePos)
{
    Vector2 direcVector = {mousePos.x - player.spaceship.x, mousePos.y - player.spaceship.y};
    Vector2 normVector = Vector2Normalize(direcVector);

    float speed = 0.750f;
    Vector2 maxVelocity = { 100.0f, 100.0f };
    maxVelocity = Vector2Normalize(maxVelocity);
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        player.aceleration.x += normVector.x;
        player.aceleration.y += normVector.y;
    }

    player.spaceship.x += player.aceleration.x*GetFrameTime();
    player.spaceship.y += player.aceleration.y*GetFrameTime();

    WarpCoords(player);
}

void WarpCoords(Spaceship& player)
{
    if (player.spaceship.x < 0)
        player.spaceship.x += GetScreenWidth();
    
    if (player.spaceship.y < 0)
        player.spaceship.y += GetScreenHeight();
    
    if (player.spaceship.x > GetScreenWidth())
        player.spaceship.x -= GetScreenWidth();
    
    if(player.spaceship.y > GetScreenHeight())
        player.spaceship.y -= GetScreenHeight(); 
}


float RepositionSpaceship(Rectangle spaceship)
{
    Vector2 direcVector = {GetMouseX() - spaceship.x, GetMouseY() - spaceship.y};

    float angle = atan(direcVector.y / direcVector.x);

    angle *= 180 / acos(-1.0f); //CONVERSION RAD TO DEG
    
    if (direcVector.x < 0)
        angle += 180;
    
    return angle;
}


void DrawSpaceship(Rectangle spaceship, float playerRotation, Texture2D spaceshipTexture)
{
    int frameWidth = spaceshipTexture.width;
    int frameHeight = spaceshipTexture.height;
    Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
    const Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
    Vector2 origin = {spaceship.width/2-spaceship.width/10 , spaceship.height / 2};
    DrawTexturePro(spaceshipTexture, sourceRec, spaceship, origin, playerRotation, NEONCYAN);
    DrawRectangleLinesEx(spaceship, 2.0f, NEONCYAN);
}

Spaceship InitSpaceship()
{
    Rectangle spaceship;
    spaceship.x = GetScreenWidth() / 2.0f;
    spaceship.y = GetScreenHeight() / 2.0f;
    spaceship.width = GetScreenWidth() / 20.0f;
    spaceship.height = GetScreenHeight() / 20.0f;
    Vector2 velocity{};
    float aceleration = 200.0f;
    int lives = 3;
    bool isAlive = true;
    return {spaceship, aceleration, aceleration, velocity.x, velocity.y, lives, isAlive};
}
