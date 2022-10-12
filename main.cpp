
#include "menu.h"
#include "RunGame.h"

int main() 
{
	constexpr int width = 1080;
	constexpr int height = 920;
	InitWindow(width, height, "Asteroids");
	RunGame();
	//Menu();
	return 0;
}