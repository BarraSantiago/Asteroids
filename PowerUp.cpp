#include "PowerUp.h"

#include <raylib.h>

#include "Circle.h"

extern float powerUp1Timer;
extern bool isPowerUp1;
extern Circle powerUp1;

void PowerUp()
{
    if (powerUp1Timer <= 0 && !isPowerUp1)
    {
        float x = static_cast<float>(GetRandomValue(0, GetScreenWidth()));
        float y = static_cast<float>(GetRandomValue(0, GetScreenHeight()));
        powerUp1 = {x, y, static_cast<float>(GetScreenWidth()) / 35.0f};
        isPowerUp1 = true;
    }
    else
    {
        powerUp1Timer -= GetFrameTime();
    }
}

void DrawPowerUp()
{
    constexpr Color altBlue = {0, 121, 241, 130};
    if (isPowerUp1)
    {
        DrawCircle(static_cast<int>(powerUp1.x), static_cast<int>(powerUp1.y), powerUp1.radius, altBlue);
    }
}
