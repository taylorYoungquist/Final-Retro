#include "Bullets.h"
#include "AIE.h"
#include "Enemies.h"

Bullets::Bullets()
{
	height = 10;
	width = 5;
}

void Bullets::Init()
{
	spriteID = CreateSprite("./images/bullets.png", width, height, true);
}
Bullets::~Bullets()
{
}

void Bullets::SetPosition(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}

void Bullets::SetSize(float a_width, float a_height)
{
	width = a_width;
	height = a_height;
}