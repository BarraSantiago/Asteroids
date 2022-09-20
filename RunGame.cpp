#include "RunGame.h"

using namespace std;

void RunGame() 
{
	int width = 720;
	int height = 480;
	
	float playerRotation=0.01f;
	
	InitWindow(width, height, "Asteroids");
	
	Vector2 mousePos = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	Rectangle player = InitPlayer();

	
	while (!WindowShouldClose())
	{
		DrawGame(player, playerRotation, mousePos);

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			mousePos = GetMousePosition();
			playerRotation = RepositionPlayer(player);
		}

		MovePlayer(player, mousePos);
	}

	CloseWindow();

}

void MovePlayer(Rectangle& player, Vector2 mousePos)
{

	/*if (player.x > mousePos.x)
		player.x -= 400.0f * GetFrameTime();
	else if (player.x < mousePos.x)
		player.x += 400.0f * GetFrameTime();

	if (player.y > mousePos.y)
		player.y -= 400.0f * GetFrameTime();
	else if (player.y < mousePos.y)
		player.y += 400.0f * GetFrameTime();*/

	Vector2 direcVector = { GetMouseX() - player.x, GetMouseY() - player.y };
	Vector2 normVector = { direcVector.x / sqrt(direcVector.x* direcVector.x), direcVector.y / sqrt(direcVector.y * direcVector.y) };
	player.x -= (400.0f + normVector.x) * GetFrameTime();
	player.y -= (400.0f + normVector.y) * GetFrameTime();
}

float RepositionPlayer(Rectangle player)
{
	Vector2 direcVector = { GetMouseX() - player.x, GetMouseY() - player.y };

	float angle = atan(direcVector.y / direcVector.x);
	
	angle *= 180 / acos(-1.0f); //CONVERSION RAD TO DEG
	
	return angle;
}

void DrawGame(Rectangle player, float playerRotation, Vector2 mousePos)
{
	BeginDrawing();
	ClearBackground(BLACK);
	
	DrawLine(mousePos.x, mousePos.y, player.x, player.y, WHITE);
	DrawPlayer(player, playerRotation);

	EndDrawing();
}

void DrawPlayer(Rectangle player, float playerRotation) 
{
	const Color NEONCYAN = CLITERAL(Color) { 4, 217, 255, 255 };
	Vector2 origin = { player.width/2, player.height/2};
	DrawRectanglePro(player, origin, playerRotation, NEONCYAN);
}

Rectangle InitPlayer() 
{
	Rectangle player;
	player.x = GetScreenWidth() / 2.0f;
	player.y = GetScreenHeight() / 2.0f;
	player.width = GetScreenWidth() / 20.0f;
	player.height = GetScreenHeight() / 20.0f;
	return player;
}