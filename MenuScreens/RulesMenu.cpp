#include "RulesMenu.h"

#include <raylib.h>
#include <string>

#include "App.h"
#include "MenuEnums.h"

void DrawRules(Rectangle backRulesRec);


extern MenuOptions menuOptions;
using namespace std;

void RulesMenu()
{
    float width1 = static_cast<float>(GetScreenHeight()) / 15.0f;

    const Rectangle backRulesRec = {
        static_cast<float>(GetScreenWidth()) / 16.0f, static_cast<float>(GetScreenHeight()) / 1.7f, width1 * 2.5f,
        width1
    };

    DrawRules(backRulesRec);

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) || IsKeyPressed(KEY_ESCAPE))
    {
        if (CheckCollisionPointRec(GetMousePosition(), backRulesRec))
        {
            menuOptions = MenuOptions::menu;
        }
    }
}

void DrawRules(Rectangle backRulesRec)
{
    const int fontSize = GetScreenHeight() / 30;
    const int xPos = GetScreenWidth() / 15;

    constexpr Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
    constexpr Color DIFDARKGRAY = CLITERAL(Color){245, 245, 245, 60};
    
    BeginDrawing();

    ClearBackground(BLACK);
    DrawBackground();

    const string rulesTitle = "Rules";
    const string rulesMove = "Player:\n-Movement: Press the right mouse button to start moving";
    const string rulesAttack =
        "-Attack: Press the left mouse button to shoot\n-Esc: While in game, pess Esc to return to menu";
    const string rulesPowerUpA = "Power Ups:\n-Shield: Grabbing the blue shield gives 4 seconds of damage immunity.";
    const string rulesWinCon = "Win Condition: In order to win, you need to destoy all asteroids.";
    const string rulesBack = "Back";

    if (CheckCollisionPointRec(GetMousePosition(), backRulesRec))
    {
        DrawRectangleRec(backRulesRec, DIFDARKGRAY);
    }

    DrawText(rulesTitle.c_str(), xPos, GetScreenHeight() / 10, fontSize * 2, WHITE);
    DrawText(rulesMove.c_str(), xPos, GetScreenHeight() / 6, fontSize, NEONCYAN);
    DrawText(rulesAttack.c_str(), xPos, GetScreenHeight() / 4, fontSize, NEONCYAN);
    DrawText(rulesPowerUpA.c_str(), xPos, static_cast<int>(GetScreenHeight() / 2.7f), fontSize, NEONCYAN);
    DrawText(rulesWinCon.c_str(), xPos, GetScreenHeight() / 2, fontSize, NEONCYAN);
    DrawText(rulesBack.c_str(), xPos, static_cast<int>(GetScreenHeight() / 1.7f), fontSize * 2, WHITE);

    EndDrawing();
}
