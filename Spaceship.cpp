#include "Spaceship.h"

#include <cmath>


static float acelerationX = 0.1f;
static float acelerationY = 0.1f;

void MovePlayer(Rectangle& player, Vector2 mousePos)
{
    Vector2 direcVector = {mousePos.x - player.x, mousePos.y - player.y};

    float moduleVector = sqrt(direcVector.x * direcVector.x + direcVector.y * direcVector.y);

    Vector2 normVector = {direcVector.x / moduleVector, direcVector.y / moduleVector};

    float speed = 500.0f;

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        acelerationX += speed * normVector.x * GetFrameTime();
        acelerationY += speed * normVector.y * GetFrameTime();
    }
    
    player.x += acelerationX;
    player.y += acelerationY;
    
    /*
    if (player.x > mousePos.x)
        player.x -= (speed + normVector.x) * GetFrameTime();
    if (player.x < mousePos.x)
        player.x += (speed + normVector.x) * GetFrameTime();

    if (player.y > mousePos.y)
        player.y -= (speed + normVector.y) * GetFrameTime();
    if (player.y < mousePos.y)
        player.y += (speed + normVector.y) * GetFrameTime();
        */
}

float RepositionSpaceship(Rectangle spaceship)
{
    Vector2 direcVector = {GetMouseX() - spaceship.x, GetMouseY() - spaceship.y};

    float angle = atan(direcVector.y / direcVector.x);

    angle *= 180 / acos(-1.0f); //CONVERSION RAD TO DEG
    if(direcVector.x < 0 )
        angle +=180;
    return angle;
}


void DrawSpaceship(Rectangle player, float playerRotation)
{
    const Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
    Vector2 origin = {player.width / 2, player.height / 2};
    DrawRectanglePro(player, origin, playerRotation, NEONCYAN);
}

Spaceship InitSpaceship()
{
    Rectangle spaceship;
    spaceship.x = GetScreenWidth() / 2.0f;
    spaceship.y = GetScreenHeight() / 2.0f;
    spaceship.width = GetScreenWidth() / 20.0f;
    spaceship.height = GetScreenHeight() / 20.0f;
    
    float aceleration = 400.0f;
    
    int lives = 3;
    
    bool isAlive=true;
    
    return {spaceship,aceleration,lives,isAlive};
}