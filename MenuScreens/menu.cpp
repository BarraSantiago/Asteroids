#include "menu.h"
#include <iostream>

#include "MainMenu.h"
#include "MenuEnums.h"
#include "../RunGame.h"
#include "raylib.h"

using namespace std;

#pragma region functions

void OptionsMenu(int& screenWidth, int& screenHeight);
void DrawOptions(Rectangle backBackRec, Rectangle screenSizeA, Rectangle screenSizeB, Rectangle bgMusic,
                 Rectangle soundRec);
void RulesMenu();
void DrawRules(Rectangle backRulesRec);
void CreditsMenu();
void DrawCredits(Rectangle backCreditsRec);
#pragma endregion

#pragma region globalVariables
static float height;
static float width1;
bool music = true;
bool sound = true;
bool debugMode = false;
Texture2D backgroundTexture;
MenuOptions menuOptions = MenuOptions::menu;
static constexpr Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
static constexpr Color DIFDARKGRAY = CLITERAL(Color){245, 245, 245, 60};
Image logo;
static string credits[6];
#pragma endregion

void Menu()
{
    int screenWidth = 1280;
    int screenHeight = 960;
    constexpr char Title[] = "Asteroids";

    InitWindow(screenWidth, screenHeight, Title);

    backgroundTexture = LoadTexture("res/asteroids_background.png");

    height = static_cast<float>(GetScreenHeight());
    width1 = static_cast<float>(GetScreenHeight()) / 15.0f;

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

void RulesMenu()
{
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

static Rectangle linkedinRec;
static Rectangle itchioRec;
static Rectangle creditsRec[6];

void CreditsMenu()
{
    const int xPos = GetScreenWidth() / 15;
    const int fontSize = GetScreenHeight() / 30;
    const int yPos1 = static_cast<int>(static_cast<float>(GetScreenHeight()) / 2.7f);

    const float linkedinSize = static_cast<float>(MeasureText("Linkedin", static_cast<int>(fontSize * 1.5f)));
    const float creditSize = static_cast<float>(MeasureText("SantiagoBarra", static_cast<int>(fontSize * 4.07f)));

    const Rectangle backCreditsRec = {
        static_cast<float>(GetScreenWidth()) / 16.0f, static_cast<float>(GetScreenHeight()) / 1.3f, width1 * 2.5f,
        width1
    };
    linkedinRec = {xPos + creditSize / 1.01f, GetScreenHeight() / 4.4f, linkedinSize * 1.1f, fontSize * 1.4f};
    itchioRec = {xPos + creditSize / 1.01f, GetScreenHeight() / 3.7f, linkedinSize * 1.1f, fontSize * 1.4f};

    for (int i = 0; i < 6; ++i)
    {
        float y = static_cast<float>(yPos1) * (1.0f + 0.15f * static_cast<float>(i));
        creditsRec[i] = {
            static_cast<float>(xPos), y,
            static_cast<float>(MeasureText(credits[4].c_str(), static_cast<int>(fontSize * 1.5f))),
            static_cast<float>(fontSize) * 1.4f
        };
    }

    DrawCredits(backCreditsRec);
    string creditsUrl[6];
    creditsUrl[0] = "https://www.vhv.rs/viewpic/iobbxmo_heart-pixel-art-hd-png-download/";
    creditsUrl[1] = "http://millionthvector.blogspot.com/p/free-sprites.html";
    creditsUrl[2] = "https://www.reddit.com/r/PixelArt/comments/a4fp0e/supermassive_black_hole/";
    creditsUrl[3] = "https://www.kindpng.com/imgv/wmmowx_pixel-art-asteroid-sprite-hd-png-download/";
    creditsUrl[4] = "https://mixkit.co/free-sound-effects/space-shooter/";
    creditsUrl[5] = "https://freesound.org/people/Clinthammer/sounds/179511/";

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(GetMousePosition(), backCreditsRec))
        {
            menuOptions = MenuOptions::menu;
        }
        else if (CheckCollisionPointRec(GetMousePosition(), linkedinRec))
        {
            OpenURL("https://www.linkedin.com/in/santiago-barra-13a849236/");
        }
        else if (CheckCollisionPointRec(GetMousePosition(), itchioRec))
        {
            OpenURL("https://santiagobarra.itch.io/");
        }
        else
        {
            for (int i = 0; i < 6; ++i)
            {
                if (CheckCollisionPointRec(GetMousePosition(), creditsRec[i]))
                {
                    OpenURL(creditsUrl[i].c_str());
                }
            }
        }
    }
}

void DrawCredits(Rectangle backCreditsRec)
{
    const int xPos = GetScreenWidth() / 15;

    const int yPos1 = static_cast<int>(static_cast<float>(GetScreenHeight()) / 2.7f);
    const int fontSize = GetScreenHeight() / 30;
    const int fontSize1 = static_cast<int>(static_cast<float>(fontSize) * 1.5f);

    BeginDrawing();
    ClearBackground(BLACK);
    DrawBackground();


    const string creditsTitle = "MADE BY";
    const string creditsCredit = "SantiagoBarra";
    const string creditsLinkedin = "Linkedin";
    const string creditsItchio = "Itchio";

    credits[0] = "Bullet sprite by Matthew Mcconaughey";
    //https://www.vhv.rs/viewpic/iobbxmo_heart-pixel-art-hd-png-download/
    credits[1] = "Spaceship sprite by MillionthVector"; //http://millionthvector.blogspot.com/p/free-sprites.html
    credits[2] = "Background art by mentalpoppixels";
    //https://www.reddit.com/r/PixelArt/comments/a4fp0e/supermassive_black_hole/
    credits[3] = "Asteroid sprite by Sarah Reddington";
    //https://www.kindpng.com/imgv/wmmowx_pixel-art-asteroid-sprite-hd-png-download/
    credits[4] = "Shoot and hit sound effect from mixkit.co"; //https://mixkit.co/free-sound-effects/space-shooter/
    credits[5] = "Backgroun sound by Clinthammer"; //https://freesound.org/people/Clinthammer/sounds/179511/
    const string rulesBack = "Back";

    if (CheckCollisionPointRec(GetMousePosition(), backCreditsRec))
    {
        DrawRectangleRec(backCreditsRec, DIFDARKGRAY);
    }
    if (CheckCollisionPointRec(GetMousePosition(), linkedinRec))
    {
        DrawRectangleRec(linkedinRec, DIFDARKGRAY);
    }
    else if (CheckCollisionPointRec(GetMousePosition(), itchioRec))
    {
        DrawRectangleRec(itchioRec, DIFDARKGRAY);
    }
    else
    {
        for (int i = 0; i < 6; ++i)
        {
            if (CheckCollisionPointRec(GetMousePosition(), creditsRec[i]))
            {
                DrawRectangleRec(creditsRec[i], DIFDARKGRAY);
                break;
            }
        }
    }
    DrawText(creditsTitle.c_str(), xPos, GetScreenHeight() / 9, fontSize * 2, WHITE);
    DrawText(creditsCredit.c_str(), xPos, GetScreenHeight() / 5, fontSize * 4, NEONCYAN);
    DrawText(creditsLinkedin.c_str(), xPos + MeasureText(creditsCredit.c_str(), static_cast<int>(fontSize * 4.07f)),
             static_cast<int>(GetScreenHeight() / 4.4), static_cast<int>(fontSize * 1.5), WHITE);
    DrawText(creditsItchio.c_str(), xPos + MeasureText(creditsCredit.c_str(), static_cast<int>(fontSize * 4.07f)),
             static_cast<int>(GetScreenHeight() / 3.7), static_cast<int>(fontSize * 1.5), WHITE);
    for (int i = 0; i < 6; ++i)
    {
        int y = static_cast<int>(static_cast<float>(yPos1) * (1.0f + 0.15f * static_cast<float>(i)));
        DrawText(credits[i].c_str(), xPos, y, fontSize1, DARKGRAY);
    }

    DrawText(rulesBack.c_str(), xPos, static_cast<int>(GetScreenHeight() / 1.3f), fontSize * 2, WHITE);

    EndDrawing();
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
