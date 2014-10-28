#include "Enemies.h"
#include "AIE.h"
Enemies::Enemies()
{
	dir = -1;
	speed = 200.f;
	width = 50;
	height = 50;
	leftExt = 0;
	x = leftExt + height *.5f;
	y = 800;
	rightExt = 600;
	bottomExt = 0 + height *.5f;
	topExt = 800;
	spriteID = CreateSprite("./images/enemy.png", width, height, true);
}


Enemies::~Enemies()
{
}


void Enemies::SetPosition(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}

void Enemies::SetSize(float a_width, float a_height)
{
	width = a_width;
	height = a_height;
}

void Enemies::SetMovementExt(float a_leftExt, float a_rightExt, float a_bottomExt, float a_topExt)
{
	leftExt = a_leftExt;
	rightExt = a_rightExt;
	bottomExt = a_bottomExt;
	topExt = a_topExt;
}

void Enemies::Movement(float a_deltaTime)
{
	if (y <= bottomExt)
	{
		y = bottomExt;
		dir *= -1;
		RotateSprite(spriteID, 180);
	}

	if (y >= topExt)
	{
		y = topExt;
		dir *= -1;
		RotateSprite(spriteID, 180);
	}
	y += speed * dir * a_deltaTime;
	
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}

bool Enemies::Collide()
{
	while (x - width * .5f <= player.x + player.width *.5f &&
		x + width * .5f >= player.x - player.width * .5f &&
		y - height * .5f <= player.y + player.height * .5f &&
		y + height * .5f >= player.y - player.height * .5f)
	{
		return true;
	}
	return false;
}