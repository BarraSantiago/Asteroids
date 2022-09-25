#include "Spaceship.h"
#include "raymath.h"
#include <cmath>


void MovePlayer(Spaceship& player, Vector2 mousePos)
{
    Vector2 direcVector = {mousePos.x - player.spaceShip.x, mousePos.y - player.spaceShip.y};
    Vector2 normVector = Vector2Normalize(direcVector);
    float speed = 1.0f;
    
    //float moduleVector = sqrt(direcVector.x * direcVector.x + direcVector.y * direcVector.y);

    //Vector2 normVector;// = {direcVector.x / moduleVector, direcVector.y / moduleVector};
    
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        player.aceleration.x = normVector.x ;
        player.aceleration.y = normVector.y ;
        if (player.velocity.x < 50.0f)
        {
            player.velocity.x += player.aceleration.x * GetFrameTime() * speed;
        }
        if (player.velocity.y < 50.0f)
        {
            player.velocity.y += player.aceleration.y * GetFrameTime() * speed;
        }
    }
 
    player.spaceShip.x += player.velocity.x;
    player.spaceShip.y += player.velocity.y;
    if(player.spaceShip.x<=0)
    {
        
    }
    /*
    if (player.spaceShip.x > mousePos.x)
        player.spaceShip.x -= (speed + normVector.x) * GetFrameTime();
    if (player.spaceShip.x < mousePos.x)
        player.spaceShip.x += (speed + normVector.x) * GetFrameTime();

    if (player.spaceShip.y > mousePos.y)
        player.spaceShip.y -= (speed + normVector.y) * GetFrameTime();
    if (player.spaceShip.y < mousePos.y)
        player.spaceShip.y += (speed + normVector.y) * GetFrameTime();
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
    Vector2 velocity{};
    float aceleration = 400.0f;
    
    int lives = 3;
    
    bool isAlive=true;
    
    return {spaceship,aceleration, aceleration, velocity.x, velocity.y,lives,isAlive};
}