#include "RunGame.h"

using namespace std;

void RunGame() 
{
	int width = 720;
	int height = 480;
	
	float playerRotation=0.01f;

	Bullet bullets[5];
	
	InitWindow(width, height, "Asteroids");
	
	Vector2 mousePos = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
	Rectangle player = InitPlayer();

	
	while (!WindowShouldClose())
	{
		DrawGame(player, playerRotation, mousePos, bullets);

		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
			mousePos = GetMousePosition();
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			Shoot(player,mousePos, bullets);
		playerRotation = RepositionPlayer(player);

		MovePlayer(player, mousePos);
	}

	CloseWindow();

}

void Shoot(Rectangle player, Vector2 mousePos, Bullet bullets[])
{
	int aux=0;
	for (int i = 0; i < 5; ++i)
	{
		if (!bullets[i].isAlive)
		{
			aux = i;
			break;
		}
	}
	bullets[aux].direction = { mousePos.x - player.x, mousePos.y - player.y };
	bullets[aux].position = { player.x, player.y };
	bullets[aux].size = GetScreenWidth()/80;
	bullets[aux].isAlive = true;
}
void DrawBullets(Bullet bullets[])
{
	for (int i = 0; i < 5; ++i)
	{
		if (bullets[i].isAlive)
			DrawCircle(static_cast<int>(bullets[i].position.x), static_cast<int>(bullets[i].position.y), static_cast<float>(bullets[i].size), WHITE );
	}
}
void MovePlayer(Rectangle& player, Vector2 mousePos)
{
	/*
	if (player.x > mousePos.x)
		player.x -= 250.0f * GetFrameTime();
	else if (player.x < mousePos.x)
		player.x += 250.0f * GetFrameTime();

	if (player.y > mousePos.y)
		player.y -= 250.0f * GetFrameTime();
	else if (player.y < mousePos.y)
		player.y += 250.0f * GetFrameTime();
	*/
	
	Vector2 direcVector = { mousePos.x - player.x, mousePos.y - player.y };
	
	float moduleVector = sqrt(direcVector.x* direcVector.x + direcVector.y * direcVector.y);
	
	Vector2 normVector = {direcVector.x/moduleVector, direcVector.y/moduleVector};
	
	float speed = 400.0f;
	if(player.x>mousePos.x)
		player.x -= (speed+normVector.x) * GetFrameTime();
	if(player.x<mousePos.x)
		player.x += (speed+normVector.x) * GetFrameTime();
	
	if(player.y>mousePos.y)
		player.y -= (speed+normVector.y) * GetFrameTime();
	if(player.y<mousePos.y)
		player.y += (speed+normVector.y) * GetFrameTime();

}

float RepositionPlayer(Rectangle player)
{
	Vector2 direcVector = { GetMouseX() - player.x, GetMouseY() - player.y };

	float angle = atan(direcVector.y / direcVector.x);
	
	angle *= 180 / acos(-1.0f); //CONVERSION RAD TO DEG
	
	return angle;
}

void DrawGame(Rectangle player, float playerRotation, Vector2 mousePos, Bullet bullets[])
{
	BeginDrawing();
	ClearBackground(BLACK);
	
	DrawLine(mousePos.x, mousePos.y, player.x, player.y, WHITE);
	DrawBullets(bullets);
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