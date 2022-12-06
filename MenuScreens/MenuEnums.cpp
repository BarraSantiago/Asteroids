#include "MenuEnums.h"

#include <raylib.h>

MenuUI InitMenuUI()
{
    const int fontSize = GetScreenHeight() / 9;
    const float xPosition = static_cast<float>(GetScreenWidth()) / 25.0f;
    const float yPosition = static_cast<float>(GetScreenHeight()) / 9.0f;
    const float xRepos = xPosition - xPosition / 5;
    const float yRepos = yPosition / 20;
    return {fontSize, xPosition, yPosition, xRepos, yRepos};
}
