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
	b = { a.x-50, a.y-75 };
	c = { a.x+50, a.y-75 };
	string bLocX = to_string(b.x);
	string bLocY = to_string(b.y);
	string cLocX = to_string(c.x);
	string cLocY = to_string(c.y);
	DrawText(bLocX.c_str,GetScreenWidth()/2,GetScreenHeight()/2, GetScreenHeight()/13, WHITE);
	DrawText(bLocY.c_str,GetScreenWidth()/2,GetScreenHeight()/2-50, GetScreenHeight()/13, WHITE);
	DrawText(cLocX.c_str,GetScreenWidth()/2,GetScreenHeight()/2-100, GetScreenHeight()/13, WHITE);
	DrawText(cLocY.c_str,GetScreenWidth()/2,GetScreenHeight()/2-150, GetScreenHeight()/13, WHITE);
	DrawTriangle(a,b,c, NEONCYAN);
}