#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "AIE.h"
#include <fstream>


class Player
{
public:
	Player();
	~Player();

	int player;
	
	static int score;

	void Init();

	float x;
	float y;
	float width;
	float height;

	void MovementKeys(float a_deltaTime);

	void AddScore(int a_score);
	void GetScore(char* a_result);

};

#endif