#include "RunGame.h"

using namespace std;

void RunGame() 
{
	int width = 720;
	int height = 480;
	InitWindow(width, height, "Asteroids");


	while (!WindowShouldClose())
	{
		DrawGame();
	}

	CloseWindow();

}

void DrawGame()
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawPlayer();
	EndDrawing();
}

void DrawPlayer() 
{
	const Color NEONCYAN = CLITERAL(Color) { 4, 217, 255, 255 };
	Vector2 a, b, c;
	a = GetMousePosition();
	b = { a.x-50, a.y-50 };
	c = { a.x+50, a.y+50 };

	DrawText(TextFormat("b.x: %i", (int)b.x), GetScreenWidth() / 2, GetScreenHeight() / 2, GetScreenHeight() / 13, WHITE);
	DrawText(TextFormat("b.y: %i", (int)b.y), GetScreenWidth() / 2, GetScreenHeight() / 2 + 50, GetScreenHeight() / 13, WHITE);
	DrawText(TextFormat("c.x: %i", (int)c.x), GetScreenWidth() / 2, GetScreenHeight() / 2 + 100, GetScreenHeight() / 13, WHITE);
	DrawText(TextFormat("c.y: %i", (int)c.y),GetScreenWidth() / 2,GetScreenHeight() /   2 + 150, GetScreenHeight()/13, WHITE);
	DrawTriangle(a,b,c, NEONCYAN);
}