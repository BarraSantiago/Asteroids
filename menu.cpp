#include "menu.h"
#include <iostream>
#include "RunGame.h"

using namespace std;

void Menu()
{
    int screenWidth = 1280;
    int screenHeight = 960;
    bool p2Active = true;
    const char Title[] = "Asteroids";

    MenuOptions menuOptions = MenuOptions::menu;

    InitWindow(screenWidth, screenHeight, Title);

    while (!WindowShouldClose() && menuOptions != MenuOptions::exit)
    {
        switch (menuOptions)
        {
        case MenuOptions::menu:
            MainMenu(menuOptions);
            break;
        case MenuOptions::play:
            RunGame();
            break;
        case MenuOptions::options:
            OptionsMenu(menuOptions, screenWidth, screenHeight, p2Active);
            break;
        case MenuOptions::rules:
            RulesMenu(menuOptions);
            break;
        case MenuOptions::credits:
            CreditsMenu(menuOptions);
            break;
        case MenuOptions::exit:
            CloseWindow();
            break;
        default:
            break;
        }
    }
    CloseWindow();
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

void MainMenu(MenuOptions& menuOptions)
{
    Rectangle menuRectangles[6];

    MenuUI menuUI = InitMenuUI();

    for (int i = static_cast<int>(MenuOptions::exit); i != static_cast<int>(MenuOptions::menu); --i)
    {
        menuRectangles[i] = {
            menuUI.xRepos,
            static_cast<float>(GetScreenHeight()) - menuUI.yPosition * (static_cast<int>(MenuOptions::exit) -
                static_cast<float>(i) + 1.45f)
            + menuUI.yRepos,
            static_cast<float>(menuUI.fontSize) * 3.9f, static_cast<float>(menuUI.fontSize)
        };
    }

    Vector2 mousePos = GetMousePosition();

    DrawMainMenu(menuUI, menuRectangles);

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(mousePos, menuRectangles[static_cast<int>(MenuOptions::play)]))
            menuOptions = MenuOptions::play;

        else if (CheckCollisionPointRec(mousePos, menuRectangles[static_cast<int>(MenuOptions::options)]))
            menuOptions = MenuOptions::options;

        else if (CheckCollisionPointRec(mousePos, menuRectangles[static_cast<int>(MenuOptions::rules)]))
            menuOptions = MenuOptions::rules;

        else if (CheckCollisionPointRec(mousePos, menuRectangles[static_cast<int>(MenuOptions::credits)]))
            menuOptions = MenuOptions::credits;

        else if (CheckCollisionPointRec(mousePos, menuRectangles[static_cast<int>(MenuOptions::exit)]))
            menuOptions = MenuOptions::exit;
    }
}

void DrawMainMenu(MenuUI menuUI, Rectangle menuRectangles[])
{
    const Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};

    BeginDrawing();

    for (int i = static_cast<int>(MenuOptions::exit); i != static_cast<int>(MenuOptions::menu); --i)
    {
        DrawRectangleRec(menuRectangles[i],
                         CheckCollisionPointRec(GetMousePosition(), menuRectangles[i]) ? DARKGRAY : BLACK);
    }

    DrawText("Pong", GetScreenWidth() / 2 - GetScreenHeight() / 6, GetScreenHeight() / 25, GetScreenHeight() / 7,
             WHITE);

    string options[] = {"menu", "Play", "Options", "Rules", "Credits", "Exit"};

    for (int i = static_cast<int>(MenuOptions::exit); i != static_cast<int>(MenuOptions::menu); --i)
    {
        DrawText(options[i].c_str(), static_cast<int>(menuUI.xPosition),
                 static_cast<int>(static_cast<float>(GetScreenHeight()) - menuUI.yPosition * (6.4f - static_cast<float>(
                     i))),
                 menuUI.fontSize, NEONCYAN);
    }

    ClearBackground(BLACK);

    EndDrawing();
}
    static const float height = static_cast<float>(GetScreenHeight());
    static const float width1 = static_cast<float>(GetScreenHeight()) / 15.0f;
    
void OptionsMenu(MenuOptions& menuOptions, int& screenWidth, int& screenHeight, bool& p2Active)
{
    const float xPos = static_cast<float>(GetScreenWidth()) / 16.0f;
    const float height2 = static_cast<float>(GetScreenHeight()) / 17.0f;
    const Rectangle backBackRec = {xPos, height / 1.8f, width1 * 2.5f, width1};
    const Rectangle screenSizeA = {xPos, height / 3.6f, width1 * 3.5f, height2};
    const Rectangle screenSizeB = {xPos * 4.15f, height / 3.6f, width1 * 4.3f,height2};
    const Rectangle onePlayer = {xPos, height / 2.2f, width1 * 3.7f, height2};
    const Rectangle twoPlayers = {xPos * 4.5f, height / 2.2f, width1 * 4.8f,height2};

    DrawOptions(backBackRec, screenSizeA, screenSizeB, onePlayer, twoPlayers);

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
        if (CheckCollisionPointRec(GetMousePosition(), backBackRec))
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
        else if (CheckCollisionPointRec(GetMousePosition(), onePlayer))
            p2Active = false;
        else if (CheckCollisionPointRec(GetMousePosition(), twoPlayers))
            p2Active = true;
    }
}

void DrawOptions(Rectangle backBackRec, Rectangle screenSizeA, Rectangle screenSizeB, Rectangle onePlayer,
                 Rectangle twoPlayers)
{
    const Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
    const int xPos = GetScreenWidth() / 15;
    const int fontSize = GetScreenHeight() / 30;
    const int fontSize1 = static_cast<int>(static_cast<float>(fontSize) * 1.5f);

    BeginDrawing();

    const string optionsTitle = "OPTIONS";
    const string optionsChangeSize = "Cambiar resolucion de pantalla";
    const string optionsSizeA = "1280x920";
    const string optionsSizeB = "Fullscreen";
    const string p2Active = "Cantidad de Jugadores";
    const string onePlayerStr = "1 jugador";
    const string twoPlayersStr = "2 jugadores";
    const string rulesBack = "Back";

    DrawRectangleRec(backBackRec, CheckCollisionPointRec(GetMousePosition(), backBackRec) ? DARKGRAY : BLACK);
    DrawRectangleRec(screenSizeA, CheckCollisionPointRec(GetMousePosition(), screenSizeA) ? DARKGRAY : BLACK);
    DrawRectangleRec(screenSizeB, CheckCollisionPointRec(GetMousePosition(), screenSizeB) ? DARKGRAY : BLACK);
    DrawRectangleRec(onePlayer, CheckCollisionPointRec(GetMousePosition(), onePlayer) ? DARKGRAY : BLACK);
    DrawRectangleRec(twoPlayers, CheckCollisionPointRec(GetMousePosition(), twoPlayers) ? DARKGRAY : BLACK);

    DrawText(optionsTitle.c_str(),      xPos, GetScreenHeight() / 9, static_cast<int>(static_cast<float>(fontSize) * 2.3f), WHITE);
    DrawText(optionsChangeSize.c_str(), xPos, GetScreenHeight() / 5, fontSize1, WHITE);
    DrawText(optionsSizeA.c_str(),      xPos, static_cast<int>(height / 3.5f),fontSize1, NEONCYAN);
    DrawText(optionsSizeB.c_str(),  xPos * 4, static_cast<int>(height / 3.5f),fontSize1, NEONCYAN);
    DrawText(p2Active.c_str(),          xPos, static_cast<int>(height / 2.6f), fontSize * 2, WHITE);
    DrawText(onePlayerStr.c_str(),      xPos, static_cast<int>(height / 2.2f),fontSize1, NEONCYAN);
    DrawText(twoPlayersStr.c_str(), static_cast<int>(static_cast<float>(xPos) * 4.4f), static_cast<int>(height / 2.2f), fontSize1, NEONCYAN);
    DrawText(rulesBack.c_str(),         xPos, static_cast<int>(height / 1.8f), fontSize * 2, WHITE);

    ClearBackground(BLACK);

    EndDrawing();
}

void RulesMenu(MenuOptions& menuOptions)
{
    const Rectangle backRulesRec = {GetScreenWidth() / 16.0f, GetScreenHeight() / 2.0f, width1 * 2.5f, width1
    };

    DrawRules(backRulesRec);

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        if (CheckCollisionPointRec(GetMousePosition(), backRulesRec))
            menuOptions = MenuOptions::menu;
}

void DrawRules(Rectangle backRulesRec)
{
    const Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
    const int fontSize = GetScreenHeight() / 30;
    const int xPos = GetScreenWidth() / 15;

    BeginDrawing();

    const string rulesTitle = "REGLAS";
    const string rules1P = "Un Jugador:\n-movimiento: WS. Volver al menu: ESC";
    const string rules2P = "Dos Jugadores:\n-movimiento: WS y flecha hacia arriba y abajo";
    //const string rulesPowerUpA = "Poderes:\n-Dwarf Ball: Hace que la pelota se reduzca a la mitad. Se resetea cada 10 segundos.";
    //const string rulesPowerUpB = "-Grow Bar: Hace que la paleta crezca. Se resetea cada 8 segundos.";
    const string rulesBack = "Back";

    DrawRectangleRec(backRulesRec, CheckCollisionPointRec(GetMousePosition(), backRulesRec) ? DARKGRAY : BLACK);

    DrawText(rulesTitle.c_str(), xPos, GetScreenHeight() / 9, fontSize * 2, WHITE);
    DrawText(rules1P.c_str(), xPos, GetScreenHeight() / 5, fontSize, NEONCYAN);
    DrawText(rules2P.c_str(), xPos, GetScreenHeight() / 3, fontSize, NEONCYAN);
    //DrawText(rulesPowerUpA.c_str(), xPos, GetScreenHeight() / 2, fontSize * 0.9f, NEONCYAN);
    //DrawText(rulesPowerUpB.c_str(), xPos, GetScreenHeight() / 1.7, fontSize, NEONCYAN);
    DrawText(rulesBack.c_str(), xPos, static_cast<int>(static_cast<float>(GetScreenHeight()) / 1.5f), fontSize * 2, WHITE);

    ClearBackground(BLACK);

    EndDrawing();
}

void CreditsMenu(MenuOptions& menuOptions)
{
    const Rectangle backCreditsRec = {static_cast<float>(GetScreenWidth()) / 16.0f, static_cast<float>(GetScreenHeight()) / 2.0f, width1 * 2.5f, width1};

    DrawCredits(backCreditsRec);

    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        if (CheckCollisionPointRec(GetMousePosition(), backCreditsRec))
            menuOptions = MenuOptions::menu;
}

void DrawCredits(Rectangle backCreditsRec)
{
    const Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
    const int xPos = GetScreenWidth() / 15;
    const int yPos1 = static_cast<int>(static_cast<float>(GetScreenHeight()) / 2.7f);
    const int fontSize = GetScreenHeight() / 30;
    const int fontSize1 = static_cast<int>(static_cast<float>(fontSize) * 1.5f);
    BeginDrawing();

    const string creditsTitle = "MADE BY";
    const string creditsCredit = "SantiagoBarra";
    const string creditsColor = "Main Color:";
    const string creditsColorCode = " Neon Cyan {4, 217, 255}";
    const string rulesBack = "Back";

    DrawRectangleRec(backCreditsRec, CheckCollisionPointRec(GetMousePosition(), backCreditsRec) ? DARKGRAY : BLACK);

    DrawText(creditsTitle.c_str(), xPos, GetScreenHeight() / 9, fontSize * 2, WHITE);
    DrawText(creditsCredit.c_str(), xPos, GetScreenHeight() / 5, fontSize * 4, NEONCYAN);
    DrawText(creditsColor.c_str(), xPos, yPos1, fontSize1, WHITE);
    DrawText(creditsColorCode.c_str(), xPos * 4, yPos1, fontSize1, NEONCYAN);
    DrawText(rulesBack.c_str(), xPos, GetScreenHeight() / 2, fontSize * 2, WHITE);
    ClearBackground(BLACK);

    EndDrawing();
}
