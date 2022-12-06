#include "OptionsMenu.h"

#include <raylib.h>
#include <string>

#include "menu.h"
#include "MenuEnums.h"

static Rectangle debugRec;

extern bool music;
extern bool sound;
extern bool debugMode;
extern MenuOptions menuOptions;

void DrawOptions(Rectangle backBackRec, Rectangle screenSizeA, Rectangle screenSizeB, Rectangle bgMusic,
                 Rectangle soundRec);

void OptionsMenu(int& screenWidth, int& screenHeight)
{
    float height = static_cast<float>(GetScreenHeight());
    float width1 = static_cast<float>(GetScreenHeight()) / 15.0f;
    const float xPos = static_cast<float>(GetScreenWidth()) / 16.0f;
    const float height2 = static_cast<float>(GetScreenHeight()) / 17.0f;
    const Rectangle backRec = {xPos, height / 1.1f, width1 * 2.5f, width1};
    const Rectangle screenSizeA = {xPos, height / 3.6f, width1 * 3.5f, height2};
    const Rectangle screenSizeB = {xPos * 4.15f, height / 3.6f, width1 * 4.3f, height2};
    const Rectangle backgroundMusic = {xPos - xPos / 20.0f, height / 2.22f, width1 * 8.4f, height2};
    const Rectangle soundRec = {xPos - xPos / 20.0f, height / 1.93f, width1 * 8.4f, height2};
    debugRec = {xPos - xPos / 20.0f, height / 1.3f, width1 * 5.9f, height2};

    DrawOptions(backRec, screenSizeA, screenSizeB, backgroundMusic, soundRec);

    if (!IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) return;

    if (CheckCollisionPointRec(GetMousePosition(), backRec))
    {
        menuOptions = MenuOptions::menu;
    }
    else if (CheckCollisionPointRec(GetMousePosition(), screenSizeA))
    {
        screenWidth = 1280;
        screenHeight = 960;
        SetWindowSize(screenWidth, screenHeight);
    }
    else if (CheckCollisionPointRec(GetMousePosition(), screenSizeB))
    {
        screenWidth = 1920;
        screenHeight = 1080;
        SetWindowSize(screenWidth, screenHeight);
    }
    else if (CheckCollisionPointRec(GetMousePosition(), backgroundMusic))
    {
        music = !music;
    }
    else if (CheckCollisionPointRec(GetMousePosition(), soundRec))
    {
        sound = !sound;
    }
    else if (CheckCollisionPointRec(GetMousePosition(), debugRec))
    {
        debugMode = !debugMode;
    }
}

using namespace std;

void DrawOptions(Rectangle backBackRec, Rectangle screenSizeA, Rectangle screenSizeB, Rectangle bgMusic,
                 Rectangle soundRec)
{
    const int xPos = GetScreenWidth() / 15;
    const int fontSize = GetScreenHeight() / 30;
    const int fontSize1 = static_cast<int>(static_cast<float>(fontSize) * 1.5f);
    float height = static_cast<float>(GetScreenHeight());
    
    constexpr Color DIFDARKGRAY = CLITERAL(Color){245, 245, 245, 60};
    constexpr Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};

    BeginDrawing();

    ClearBackground(BLACK);
    DrawBackground();

    const string optionsTitle = "OPTIONS";
    const string optionsChangeSize = "Change screen resolution";
    const string optionsSizeA = "1280x920";
    const string optionsSizeB = "Fullscreen";
    const string p2Active = "Sounds";
    const string backgroundMusic = "Background Music";
    string isMusicActive = music ? "[a]" : "[ ]";
    const string soundString = "Sound";
    string isSoundActive = sound ? "[a]" : "[ ]";
    const string extra = "Extras";
    const string debugString = "Debug Mode";
    string isDebugActive = debugMode ? "[a]" : "[ ]";
    const string back = "Back";

    if (CheckCollisionPointRec(GetMousePosition(), backBackRec))
    {
        DrawRectangleRec(backBackRec, DIFDARKGRAY);
    }
    if (CheckCollisionPointRec(GetMousePosition(), screenSizeA))
    {
        DrawRectangleRec(screenSizeA, DIFDARKGRAY);
    }
    if (CheckCollisionPointRec(GetMousePosition(), screenSizeB))
    {
        DrawRectangleRec(screenSizeB, DIFDARKGRAY);
    }
    if (CheckCollisionPointRec(GetMousePosition(), bgMusic))
    {
        DrawRectangleRec(bgMusic, DIFDARKGRAY);
    }
    if (CheckCollisionPointRec(GetMousePosition(), soundRec))
    {
        DrawRectangleRec(soundRec, DIFDARKGRAY);
    }
    if (CheckCollisionPointRec(GetMousePosition(), debugRec))
    {
        DrawRectangleRec(debugRec, DIFDARKGRAY);
    }

    DrawText(optionsTitle.c_str(), xPos, GetScreenHeight() / 9, static_cast<int>(static_cast<float>(fontSize) * 2.3f),
             WHITE);
    DrawText(optionsChangeSize.c_str(), xPos, GetScreenHeight() / 5, fontSize1, WHITE);
    DrawText(optionsSizeA.c_str(), xPos, static_cast<int>(height / 3.5f), fontSize1, NEONCYAN);
    DrawText(optionsSizeB.c_str(), xPos * 4, static_cast<int>(height / 3.5f), fontSize1, NEONCYAN);
    DrawText(p2Active.c_str(), xPos, static_cast<int>(height / 2.6f), fontSize * 2, WHITE);
    DrawText(backgroundMusic.c_str(), xPos, static_cast<int>(height / 2.2f), fontSize1, NEONCYAN);
    DrawText(soundString.c_str(), xPos, static_cast<int>(height / 1.9f), fontSize1, NEONCYAN);
    DrawText(isMusicActive.c_str(),
             static_cast<int>(static_cast<float>(MeasureText(backgroundMusic.c_str(), fontSize1)) * 1.3f),
             static_cast<int>(height / 2.2f), fontSize1, NEONCYAN);
    DrawText(isSoundActive.c_str(),
             static_cast<int>(static_cast<float>(MeasureText(backgroundMusic.c_str(), fontSize1)) * 1.3f),
             static_cast<int>(height / 1.9f), fontSize1, NEONCYAN);
    DrawText(extra.c_str(), xPos, static_cast<int>(height / 1.4f), fontSize * 2, WHITE);
    DrawText(debugString.c_str(), xPos, static_cast<int>(height / 1.29f), fontSize1, NEONCYAN);
    DrawText(isDebugActive.c_str(),
             static_cast<int>(static_cast<float>(MeasureText(debugString.c_str(), fontSize1)) * 1.4f),
             static_cast<int>(height / 1.29f), fontSize1, NEONCYAN);
    DrawText(back.c_str(), xPos, static_cast<int>(height / 1.1f), fontSize * 2, WHITE);

    EndDrawing();
}
