#include "menu.h"
#include <iostream>

#include "CreditsMenu.h"
#include "MainMenu.h"
#include "MenuEnums.h"
#include "OptionsMenu.h"
#include "../RunGame.h"
#include "raylib.h"
#include "RulesMenu.h"

using namespace std;

#pragma region globalVariables

bool music = true;
bool sound = true;
bool debugMode = false;

Texture2D backgroundTexture;

MenuOptions menuOptions = MenuOptions::menu;

Image logo;

#pragma endregion

void Menu()
{
    int screenWidth = 1280;
    int screenHeight = 960;
    constexpr char Title[] = "Asteroids";

    InitWindow(screenWidth, screenHeight, Title);

    backgroundTexture = LoadTexture("res/asteroids_background.png");

    logo = LoadImage("res/asteroids_logo.png");
    SetWindowIcon(logo);

    while (!WindowShouldClose() && menuOptions != MenuOptions::exit)
    {
        switch (menuOptions)
        {
        case MenuOptions::menu:
            MainMenu();
            break;
        case MenuOptions::play:
            RunGame();
            break;
        case MenuOptions::options:
            OptionsMenu(screenWidth, screenHeight);
            break;
        case MenuOptions::rules:
            RulesMenu();
            break;
        case MenuOptions::credits:
            CreditsMenu();
            break;
        case MenuOptions::exit:
            CloseWindow();
            break;
        default:
            break;
        }
    }
    UnloadTexture(backgroundTexture);
}

void DrawBackground()
{
    const float frameWidth = static_cast<float>(GetScreenWidth());
    const float frameHeight = static_cast<float>(GetScreenHeight());
    const Rectangle sourceRec = {0, 0, frameWidth, frameHeight};
    const Vector2 origin = {0, 0};

    DrawTexturePro(backgroundTexture, sourceRec,
                   {0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())}, origin, 0,
                   RAYWHITE);
}
