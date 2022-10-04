#include "Bullet.h"

#include <raymath.h>

void DrawBullet(Bullet bullet);

void Shoot(Rectangle player, Vector2 mousePos, Bullet bullets[])
{
    int aux=0;
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

Bullet InitBullet(Rectangle player, Vector2 mousePos)
{
    Vector2 direction = { mousePos.x - player.x, mousePos.y - player.y };
    direction = Vector2Normalize(direction);
    Vector2 position = { player.x-player.width/1.7f, player.y };
    float speed = 400.0f;
    float size = GetScreenWidth()/160.0f;
    bool isActive = true;
    return {position, direction, speed, size, isActive};
}

void DrawBullets(Bullet bullets[])
{
    int max = sizeof(bullets);
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
    DrawCircle(static_cast<int>(bullet.position.x), static_cast<int>(bullet.position.y), static_cast<float>(bullet.radius), WHITE);
}