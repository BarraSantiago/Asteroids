#include "RunGame.h"

#include "Asteroid.h"
#include "Spaceship.h"
#include <vector>
using namespace std;

void UpdateBullets(Bullet bullets[]);
void UpdateAsteroids(vector<Asteroid> &asteroids);
void DrawGame(Rectangle player, float playerRotation, Vector2 mousePos, Bullet bullets[], Texture2D spaceshipTexture, vector<Asteroid> asteroids);
void CheckBulletAsteroidCollision(Bullet bullets[], vector<Asteroid> asteroids);
void CheckAsteroidPlayerCollision(Spaceship spaceship, vector<Asteroid> asteroids);
void UpdateObjects(Bullet bullets[], vector<Asteroid> &asteroids);

void RunGame()
{
	int width = 1080;
	int height = 920;

	InitWindow(width, height, "Asteroids");

	Bullet bullets[5];

	vector<Asteroid> asteroids;

	SpawnBigAsteroids(asteroids, 5);

	Spaceship player = InitSpaceship();
	Texture2D spaceshipTexture = LoadTexture("res/asteroids_spaceship.png");

	Vector2 mousePos = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

	while (!WindowShouldClose())
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			Shoot(player.spaceship, mousePos, bullets);

		mousePos = GetMousePosition();
		player.rotation = RepositionSpaceship(player.spaceship);
		UpdateObjects(bullets, asteroids);
		MovePlayer(player, mousePos);
		DrawGame(player.spaceship, player.rotation, mousePos, bullets, spaceshipTexture, asteroids);
	}
	UnloadTexture(spaceshipTexture);
	CloseWindow();
}

void DrawGame(Rectangle player, float playerRotation, Vector2 mousePos, Bullet bullets[], Texture2D spaceshipTexture, vector<Asteroid> asteroids)
{
	BeginDrawing();
	ClearBackground(BLACK);
	DrawLine(static_cast<int>(mousePos.x), static_cast<int>(mousePos.y), static_cast<int>(player.x), static_cast<int>(player.y), WHITE);
	DrawBullets(bullets);
	DrawSpaceship(player, playerRotation, spaceshipTexture);
	DrawAsteroids(asteroids);
	EndDrawing();
}

void UpdateObjects(Bullet bullets[], vector<Asteroid> &asteroids)
{
	UpdateAsteroids(asteroids);
	UpdateBullets(bullets);
}

void UpdateBullets(Bullet bullets[])
{
	for (int i = 0; i < 5; ++i)
	{
		if (bullets[i].isActive)
		{
			bullets[i].position.x += bullets[i].speed * bullets[i].direction.x * GetFrameTime();
			bullets[i].position.y += bullets[i].speed * bullets[i].direction.y * GetFrameTime();
			bullets[i].isActive = 0 < bullets[i].position.x && bullets[i].position.x < GetScreenWidth() && 0 < bullets[i].position.y && bullets[i].position.x < GetScreenHeight();
		}
	}
}

void UpdateAsteroids(vector<Asteroid> &asteroids)
{

	for (int i = 0; i <  static_cast<int>(asteroids.size())-1; ++i)
	{
		if (asteroids[i].isActive)
		{
			Vector2 velocity = { GetFrameTime() * asteroids[i].direction.x * asteroids[i].speed, GetFrameTime() * asteroids[i].direction.y * asteroids[i].speed };
			asteroids[i].position.x += velocity.x;
			asteroids[i].position.y += velocity.y;
			WarpAsteroid(asteroids[i]);
		}
	}
}

void UpdateCollisions(Bullet bullets[], vector<Asteroid> asteroids)
{
	CheckBulletAsteroidCollision(bullets, asteroids);
}

void CheckBulletAsteroidCollision(Bullet bullets[], vector<Asteroid> asteroids)
{
	for (int i = 0; i < static_cast<int>(asteroids.size()) - 1; i++)
	{

		float distX = bullets[i].position.x - asteroids[i].position.x;
		float distY = bullets[i].position.y - asteroids[i].position.y;
		float distance = sqrt((distX * distX) + (distY * distY));

		// if the distance is less than the sum of the circle's
		// radii, the circles are touching!
		if (distance <= bullets[i].radius + asteroids[i].position.radius)
		{
			SpawnAsteroid(asteroids, i);
		}
		else
		{

		}
	}
}

void CheckAsteroidPlayerCollision(Spaceship spaceship, vector<Asteroid> asteroids)
{
	spaceship = spaceship;
}

//void CheckAsteroidPlayerCollision(Spaceship spaceship, vector<Asteroid> asteroids)
/*

{

}
*/