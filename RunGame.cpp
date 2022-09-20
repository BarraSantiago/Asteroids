#include "RunGame.h"

using namespace std;

void RunGame() 
{
	int width = 720;
	int height = 480;
	InitWindow(width, height, "Asteroids");
	Vector2 mousePos = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	Rectangle player = InitPlayer();
	float playerRotation=0;
	while (!WindowShouldClose())
	{
		DrawGame(player, playerRotation);

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			mousePos = GetMousePosition();
			playerRotation = RepositionPlayer(player);
		}
		if (player.x > mousePos.x)
			player.x -= 400.0f * GetFrameTime();
		else if (player.x < mousePos.x)
			player.x += 400.0f * GetFrameTime();

		if (player.y > mousePos.y)
			player.y -= 400.0f * GetFrameTime();
		else if (player.y < mousePos.y)
			player.y += 400.0f * GetFrameTime();
	}

	CloseWindow();

}

float RepositionPlayer(Rectangle player)
{
	Vector2 direcVector = { GetMousePosition().x - player.x, GetMousePosition().y - player.y };

	float angle = atan(direcVector.y / direcVector.x);
	
	angle *= 180 / acos(-1.0f); //CONVERSION RAD TO DEG
	
	return angle;
}

void DrawGame(Rectangle player, float playerRotation)
{
	BeginDrawing();
	ClearBackground(BLACK);

	DrawPlayer(player, playerRotation);
	EndDrawing();
}

void DrawPlayer(Rectangle player, float playerRotation) 
{
	const Color NEONCYAN = CLITERAL(Color) { 4, 217, 255, 255 };
	Vector2 origin = { player.width/2, player.height/2};

	Rectangle rec = {};
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