#include "Bullet.h"

#include <raymath.h>

#include "DrawAdapted.h"

void DrawBullet(Bullet bullet);
extern Texture2D bulletTexture;

void Shoot(Circle player, Vector2 mousePos, Bullet bullets[])
{
    int aux = 0;
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

Bullet InitBullet(Circle player, Vector2 mousePos)
{
    Vector2 direction = {mousePos.x - player.x, mousePos.y - player.y};
    direction = Vector2Normalize(direction);
    
    const Circle body = {player.x, player.y, static_cast<float>(GetScreenWidth()) / 160.0f};
    constexpr float speed = 500.0f;
    constexpr bool isActive = true;
    return {body, direction, speed, isActive};
}

void MoveBullet(Bullet& bullet)
{
    bullet.body.x += bullet.speed * bullet.direction.x * GetFrameTime();
    bullet.body.y += bullet.speed * bullet.direction.y * GetFrameTime();
    bullet.isActive = 0 < bullet.body.x && bullet.body.x < static_cast<float>(GetScreenWidth()) && 0
        < bullet.body.y && bullet.body.y < static_cast<float>(GetScreenHeight());
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
    extern bool debugMode;
    const Rectangle sourceRec = TextureToSourceRec(bulletTexture);
    const Vector2 origin = {bullet.body.radius, bullet.body.radius};
    const Rectangle position = {bullet.body.x, bullet.body.y, bullet.body.radius * 2, bullet.body.radius * 2};

    DrawTexturePro(bulletTexture, sourceRec, position, origin, 0, RAYWHITE);

    if (debugMode)
    {
        DrawCircleLines(static_cast<int>(bullet.body.x), static_cast<int>(bullet.body.y), bullet.body.radius, RED);
    }
}
