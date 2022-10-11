#include "Spaceship.h"
#include <cmath>
#include "raymath.h"


void MovePlayer(Spaceship& player, Vector2 mousePos)
{
    Vector2 direcVector = {mousePos.x - player.body.x, mousePos.y - player.body.y};
    Vector2 normVector = Vector2Normalize(direcVector);

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        player.aceleration.x += normVector.x;
        player.aceleration.y += normVector.y;
    }

    player.body.x += (player.aceleration.x*GetFrameTime()) / 6.0f;
    player.body.y += (player.aceleration.y*GetFrameTime()) / 6.0f;

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


float RepositionSpaceship(Circle spaceship)
{
    Vector2 direcVector = {static_cast<float>(GetMouseX()) - spaceship.x, static_cast<float>(GetMouseY()) - spaceship.y};

    float angle = atan(direcVector.y / direcVector.x);

    angle *= 180 / acos(-1.0f); //CONVERSION RAD TO DEG
    
    if (direcVector.x < 0)
        angle += 180;
    
    return angle;
}


void DrawSpaceship(Circle body, float rotation, Texture2D spaceshipTexture)
{
    int frameWidth = spaceshipTexture.width;
    int frameHeight = spaceshipTexture.height;
    Rectangle sourceRec = { 0.0f, 0.0f, static_cast<float>(frameWidth), static_cast<float>(frameHeight) };
    const Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
    Vector2 origin = {body.radius/2-body.radius/10 , body.radius / 2};
    DrawTexturePro(spaceshipTexture, sourceRec, {body.x, body.y, body.radius, body.radius}, origin, rotation, NEONCYAN);
    DrawCircleLines(static_cast<int>(body.x), static_cast<int>(body.y), body.radius, NEONCYAN);
}

Spaceship InitSpaceship()
{
    Circle spaceship;
    spaceship.x = static_cast<float>(GetScreenWidth()) / 2.0f;
    spaceship.y = static_cast<float>(GetScreenHeight()) / 2.0f;
    spaceship.radius = static_cast<float>(GetScreenWidth()) / 20.0f;
    float aceleration = 0;
    int lives = 3;
    bool isAlive = true;
    return {spaceship, {aceleration, aceleration}, lives, isAlive};
}
