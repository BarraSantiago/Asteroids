#include "RunGame.h"

using namespace std;

void RunGame() 
{
	int width = 720;
	int height = 480;
	InitWindow(width, height, "Asteroids");
	Vector2 mousePos = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	Player player = InitPlayer();
	while (!WindowShouldClose())
	{
		DrawGame(player);
		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			mousePos = GetMousePosition();
		if (player.front.x > mousePos.x)
			player.front.x -= 600.0f * GetFrameTime();
		else if (player.front.x < mousePos.x)
			player.front.x += 600.0f * GetFrameTime();

		if (player.front.y > mousePos.y)
			player.front.y -= 600.0f * GetFrameTime();
		else if (player.front.y < mousePos.y)
			player.front.y += 600.0f * GetFrameTime();
	}

	CloseWindow();

}

void ReposPlayer(Player player)
{
	Vector2 mousePos = GetMousePosition();
	Vector2 direcVector = mousePos - player.front;
	float angle = 
}

void DrawGame(Player player)
{
	BeginDrawing();
	ClearBackground(BLACK);

	DrawPlayer(player);
	EndDrawing();
}

void DrawPlayer(Player player) 
{
	const Color NEONCYAN = CLITERAL(Color) { 4, 217, 255, 255 };
	player.right = { player.front.x + 50, player.front.y + 50 };
	player.left = { player.front.x - 50, player.front.y + 50 };
	//DrawText(TextFormat("c.y: %i", (int)c.y),GetScreenWidth() / 2,GetScreenHeight() /   2 + 150, GetScreenHeight()/13, WHITE);
	DrawTriangle(player.front, player.left, player.right, NEONCYAN);
}

Player InitPlayer()
{
	Player player;
	player.front = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	player.right = { player.front.x + 50, player.front.y + 50 };
	player.left = { player.front.x - 50, player.front.y + 50 };
	return player;
}