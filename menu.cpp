#include "menu.h"
#include <iostream>
#include "RunGame.h"
#include "raylib.h"

using namespace std;

#pragma region functions
void MainMenu();
void DrawMainMenu(MenuUI menuUI, Rectangle menuRectangles[]);
void OptionsMenu(int& screenWidth, int& screenHeight);
void DrawOptions(Rectangle backBackRec, Rectangle screenSizeA, Rectangle screenSizeB, Rectangle bgMusic,
                 Rectangle soundRec);
void RulesMenu();
void DrawRules(Rectangle backRulesRec);
void CreditsMenu();
void DrawCredits(Rectangle backCreditsRec);
MenuUI InitMenuUI();
#pragma endregion

#pragma region globalVariables
static float height;
static float width1;
bool music = true;
bool sound = true;
bool debugMode = true;
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

MenuUI InitMenuUI()
{
    const int fontSize = GetScreenHeight() / 9;
    const float xPosition = static_cast<float>(GetScreenWidth()) / 25.0f;
    const float yPosition = static_cast<float>(GetScreenHeight()) / 9.0f;
    const float xRepos = xPosition - xPosition / 5;
    const float yRepos = yPosition / 20;
    return {fontSize, xPosition, yPosition, xRepos, yRepos};
}

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

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mousePos, menuRectangles[static_cast<int>(MenuOptions::play)]))
        {
            menuOptions = MenuOptions::play;
        }
        else if (CheckCollisionPointRec(mousePos, menuRectangles[static_cast<int>(MenuOptions::options)]))
        {
            menuOptions = MenuOptions::options;
        }
        else if (CheckCollisionPointRec(mousePos, menuRectangles[static_cast<int>(MenuOptions::rules)]))
        {
            menuOptions = MenuOptions::rules;
        }
        else if (CheckCollisionPointRec(mousePos, menuRectangles[static_cast<int>(MenuOptions::credits)]))
        {
            menuOptions = MenuOptions::credits;
        }
        else if (CheckCollisionPointRec(mousePos, menuRectangles[static_cast<int>(MenuOptions::exit)]))
        {
            menuOptions = MenuOptions::exit;
        }
    }
}

void DrawMainMenu(MenuUI menuUI, Rectangle menuRectangles[])
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawBackground();

    for (int i = static_cast<int>(MenuOptions::exit); i != static_cast<int>(MenuOptions::menu); --i)
    {
        if (CheckCollisionPointRec(GetMousePosition(), menuRectangles[i]))
        {
            DrawRectangleRec(menuRectangles[i], DIFDARKGRAY);
        }
    }

    DrawText("Asteroids", GetScreenWidth() / 2 - MeasureText("Asteroids", GetScreenHeight() / 7) / 2,
             GetScreenHeight() / 25, GetScreenHeight() / 7, WHITE);

    string options[] = {"menu", "Play", "Options", "Rules", "Credits", "Exit"};

    for (int i = static_cast<int>(MenuOptions::exit); i != static_cast<int>(MenuOptions::menu); --i)
    {
        DrawText(options[i].c_str(), static_cast<int>(menuUI.xPosition),
                 static_cast<int>(static_cast<float>(GetScreenHeight()) - menuUI.yPosition * (6.4f - static_cast<float>(
                     i))),menuUI.fontSize, NEONCYAN);
    }

    EndDrawing();
}

static Rectangle debugRec;
void OptionsMenu(int& screenWidth, int& screenHeight)
{
    const float xPos = static_cast<float>(GetScreenWidth()) / 16.0f;
    const float height2 = static_cast<float>(GetScreenHeight()) / 17.0f;
    const Rectangle backRec = {xPos, height / 1.1f, width1 * 2.5f, width1};
    const Rectangle screenSizeA = {xPos, height / 3.6f, width1 * 3.5f, height2};
    const Rectangle screenSizeB = {xPos * 4.15f, height / 3.6f, width1 * 4.3f, height2};
    const Rectangle backgroundMusic = {xPos - xPos / 20.0f, height / 2.22f, width1 * 8.4f, height2};
    const Rectangle soundRec = {xPos - xPos / 20.0f, height / 1.93f, width1 * 8.4f, height2};
    debugRec = {xPos - xPos / 20.0f, height / 1.3f, width1 * 5.9f, height2};

    DrawOptions(backRec, screenSizeA, screenSizeB, backgroundMusic, soundRec);

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
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
        else if(CheckCollisionPointRec(GetMousePosition(), debugRec))
        {
            debugMode = !debugMode;
        }
    }
}

void DrawOptions(Rectangle backBackRec, Rectangle screenSizeA, Rectangle screenSizeB, Rectangle bgMusic,
                 Rectangle soundRec)
{
    const int xPos = GetScreenWidth() / 15;
    const int fontSize = GetScreenHeight() / 30;
    const int fontSize1 = static_cast<int>(static_cast<float>(fontSize) * 1.5f);

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
    const string rulesAttack = "-Attack: Press the left mouse button to shoot";
    const string rulesPowerUpA = "Power Ups:\n-Shield: Grabbing the blue shield gives 4 seconds of damage immunity.";
    const string rulesWinCon = "Win Condition: In order to win, you need to destoy all asteroids.";
    //const string rulesPowerUpB = "-Grow Bar: Hace que la paleta crezca. Se resetea cada 8 segundos.";
    const string rulesBack = "Back";

    if (CheckCollisionPointRec(GetMousePosition(), backRulesRec))
    {
        DrawRectangleRec(backRulesRec, DIFDARKGRAY);
    }

    DrawText(rulesTitle.c_str(), xPos, GetScreenHeight() / 10, fontSize * 2, WHITE);
    DrawText(rulesMove.c_str(), xPos, GetScreenHeight() / 6, fontSize, NEONCYAN);
    DrawText(rulesAttack.c_str(), xPos, GetScreenHeight() / 4, fontSize, NEONCYAN);
    DrawText(rulesPowerUpA.c_str(), xPos, GetScreenHeight() / 3, fontSize , NEONCYAN);
    DrawText(rulesWinCon.c_str(), xPos, GetScreenHeight() / 2, fontSize , NEONCYAN);
    //DrawText(rulesPowerUpB.c_str(), xPos, GetScreenHeight() / 1.7, fontSize, NEONCYAN);
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
            static_cast<float>(xPos), y, static_cast<float>(MeasureText(credits[4].c_str(), static_cast<int>(fontSize*1.5f))),
            static_cast<float>(fontSize) * 1.4f};
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

    credits[0] = "Bullet sprite by Matthew Mcconaughey"; //https://www.vhv.rs/viewpic/iobbxmo_heart-pixel-art-hd-png-download/
    credits[1] = "Spaceship sprite by MillionthVector"; //http://millionthvector.blogspot.com/p/free-sprites.html
    credits[2] = "Background art by mentalpoppixels"; //https://www.reddit.com/r/PixelArt/comments/a4fp0e/supermassive_black_hole/
    credits[3] = "Asteroid sprite by Sarah Reddington"; //https://www.kindpng.com/imgv/wmmowx_pixel-art-asteroid-sprite-hd-png-download/
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
