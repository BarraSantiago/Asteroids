#include "CreditsMenu.h"

#include <raylib.h>
#include <string>

#include "App.h"
#include "MenuEnums.h"

namespace barra
{
void DrawCredits(Rectangle backCreditsRec);

static Rectangle linkedinRec;
static Rectangle itchioRec;
static Rectangle creditsRec[6];
static std::string credits[6];

extern MenuOptions menuOptions;


    void CreditsMenu()
    {
        float width1 = static_cast<float>(GetScreenHeight()) / 15.0f;
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

        std::string creditsUrl[6];

        creditsUrl[0] = "https://www.vhv.rs/viewpic/iobbxmo_heart-pixel-art-hd-png-download/";
        creditsUrl[1] = "http://millionthvector.blogspot.com/p/free-sprites.html";
        creditsUrl[2] = "https://www.reddit.com/r/PixelArt/comments/a4fp0e/supermassive_black_hole/";
        creditsUrl[3] = "https://www.kindpng.com/imgv/wmmowx_pixel-art-asteroid-sprite-hd-png-download/";
        creditsUrl[4] = "https://mixkit.co/free-sound-effects/space-shooter/";
        creditsUrl[5] = "https://freesound.org/people/Clinthammer/sounds/179511/";

        if (!IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) return;

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

    using namespace std;

    void DrawCredits(Rectangle backCreditsRec)
    {
        const int xPos = GetScreenWidth() / 15;

        const int yPos1 = static_cast<int>(static_cast<float>(GetScreenHeight()) / 2.7f);
        const int fontSize = GetScreenHeight() / 30;
        const int fontSize1 = static_cast<int>(static_cast<float>(fontSize) * 1.5f);
        constexpr Color NEONCYAN = CLITERAL(Color){4, 217, 255, 255};
        constexpr Color DIFDARKGRAY = CLITERAL(Color){245, 245, 245, 60};
        BeginDrawing();
        ClearBackground(BLACK);
        DrawBackground();


        const string creditsTitle = "MADE BY";
        const string creditsCredit = "SantiagoBarra";
        const string creditsLinkedin = "Linkedin";
        const string creditsItchio = "Itchio";

        credits[0] = "Bullet sprite by Matthew Mcconaughey";
        credits[1] = "Spaceship sprite by MillionthVector";
        credits[2] = "Background art by mentalpoppixels";
        credits[3] = "Asteroid sprite by Sarah Reddington";
        credits[4] = "Shoot and hit sound effect from mixkit.co";
        credits[5] = "Backgroun sound by Clinthammer";
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
}
