#pragma once
#include <raylib.h>
#include "Circle.h"

struct Bullet
{
    Circle body;
    
    Vector2 direction;

    float speed;

    bool isActive;
};

void Shoot(Rectangle player, Vector2 mousePos, Bullet bullets[]);
void DrawBullets(Bullet bullets[]);
Bullet InitBullet(Rectangle player, Vector2 mousePos);