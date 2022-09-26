#include "Bullet.h"

void Shoot(Rectangle player, Vector2 mousePos, Bullet bullets[])
{
    int aux=0;
    for (int i = 0; i < 5; ++i)
    {
        if (!bullets[i].isActive)
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
    Vector2 position = { player.x-player.width/1.7f, player.y };
    float speed = 300.0f;
    int size = GetScreenWidth()/160;
    bool isActive = true;
    return {position, direction, speed, size, isActive};
}

void DrawBullets(Bullet bullets[])
{
    for (int i = 0; i < 5; ++i)
    {
        if (bullets[i].isActive)
            DrawCircle(static_cast<int>(bullets[i].position.x), static_cast<int>(bullets[i].position.y), static_cast<float>(bullets[i].size), WHITE );
    }
}