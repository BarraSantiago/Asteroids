#include "MainMenu.h"

#include <raylib.h>
#include <string>

#include "App.h"
#include "MenuEnums.h"

void DrawMainMenu(MenuUI menuUI, Rectangle menuRectangles[]);

void MainMenu()
{
    Rectangle menuRectangles[6];

    MenuUI menuUI = InitMenuUI();

    for (int i = static_cast<int>(MenuOptions::exit); i != static_cast<int>(MenuOptions::menu); --i)
    {
        menuRectangles[i] = {
            menuUI.xRepos,
            static_cast<float>(GetScreenHeight()) - menuUI.yPosition * (static_cast<int>(MenuOptions::exit) -
                static_cast<float>(i) + 1.45f) + menuUI.yRepos,
            static_cast<float>(menuUI.fontSize) * 3.9f, static_cast<float>(menuUI.fontSize)
        };
    }

    Vector2 mousePos = GetMousePosition();

    DrawMainMenu(menuUI, menuRectangles);

    if (!IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) return;

    for (int i = 0; i < static_cast<int>(sizeof(menuRectangles)) - 1; ++i)
    {
        if (CheckCollisionPointRec(mousePos, menuRectangles[i]))
        {
            extern MenuOptions menuOptions;
            menuOptions = static_cast<MenuOptions>(i);
        }
    }
}

void DrawMainMenu(MenuUI menuUI, Rectangle menuRectangles[])
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawBackground();

    static constexpr Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
    static constexpr Color DIFDARKGRAY = CLITERAL(Color){245, 245, 245, 60};

    for (int i = static_cast<int>(MenuOptions::exit); i != static_cast<int>(MenuOptions::menu); --i)
    {
        if (!CheckCollisionPointRec(GetMousePosition(), menuRectangles[i])) continue;

        DrawRectangleRec(menuRectangles[i], DIFDARKGRAY);
    }

    DrawText("Asteroids", GetScreenWidth() / 2 - MeasureText("Asteroids", GetScreenHeight() / 7) / 2,
             GetScreenHeight() / 25, GetScreenHeight() / 7, WHITE);

    std::string options[] = {"menu", "Play", "Options", "Rules", "Credits", "Exit"};

    for (int i = static_cast<int>(MenuOptions::exit); i != static_cast<int>(MenuOptions::menu); --i)
    {
        DrawText(options[i].c_str(), static_cast<int>(menuUI.xPosition),
                 static_cast<int>(static_cast<float>(GetScreenHeight()) - menuUI.yPosition * (6.4f - static_cast<float>(
                     i))), menuUI.fontSize, NEONCYAN);
    }

    EndDrawing();
}
