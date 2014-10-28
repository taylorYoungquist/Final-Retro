#include "AIE.h"
#include "Player.h"


Player::Player()
{
	x = 300;
	y = 200;
	width = 50;
	height = 50;
	
}
void Player::Init()
{
	player = CreateSprite("./images/Player.png", width, height, true);
}

Player::~Player()
{
	//DestroySprite(player);
}

int Player::score = 0;

void Player::AddScore(int a_score)
{
	Player::score += a_score;
}

void Player::GetScore(char* a_result)
{
	itoa(Player::score, a_result, 10);
}

void Player::MovementKeys(float a_deltaTime)
{
	if (IsKeyDown(87))
	{
		y += 150.f * a_deltaTime;
	}
	if (IsKeyDown(83))
	{
		y -= 150.f * a_deltaTime;
	}
	if (IsKeyDown(68))
	{
		x += 200.f * a_deltaTime;
	}
	if (IsKeyDown(65))
	{
		x -= 200.f * a_deltaTime;
	}
}

