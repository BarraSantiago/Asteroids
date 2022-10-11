#include "Bullet.h"

#include <raymath.h>

void DrawBullet(Bullet bullet);

void Shoot(Circle player, Vector2 mousePos, Bullet bullets[])
{
    int aux = 0;
    for (int i = 0; i < 5; ++i)
    {
        if (bullets[i].isActive == false)
        {
            aux = i;
            break;
        }
    }
    bullets[aux] = InitBullet(player, mousePos);
}

Bullet InitBullet(Circle player, Vector2 mousePos)
{
    Vector2 direction = {mousePos.x - player.x, mousePos.y - player.y};
    direction = Vector2Normalize(direction);
    Circle body = {player.x, player.y, static_cast<float>(GetScreenWidth()) / 160.0f};
    float speed = 500.0f;
    bool isActive = true;
    return {body, direction, speed, isActive};
}

void DrawBullets(Bullet bullets[])
{
    constexpr int max = sizeof(bullets);
    for (int i = 0; i < max; ++i)
    {
        if (bullets[i].isActive)
        {
            DrawBullet(bullets[i]);
        }
    }
}

void DrawBullet(Bullet bullet)
{
    DrawCircle(static_cast<int>(bullet.body.x), static_cast<int>(bullet.body.y), static_cast<float>(bullet.body.radius),
               RED);
}
