#pragma once
#include <raylib.h>

struct Bullet
{
    Vector2 position;
    Vector2 direction;
    
    float speed;

    int size;

    bool isActive;
};

void Shoot(Rectangle player, Vector2 mousePos, Bullet bullets[]);
void DrawBullets(Bullet bullets[]);
Bullet InitBullet(Rectangle player, Vector2 mousePos);