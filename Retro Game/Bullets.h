#ifndef _BULLETS_H_
#define _BULLETS_H_

#include <AIE.h>
#include <vector>

class Bullets
{
public:
	Bullets();
	~Bullets();
	unsigned int spriteID;
	float x;
	float y;
	void SetPosition(float a_x, float a_y);

	void Init();

	int height;
	int width;
	void SetSize(float a_width, float a_height);

	bool CollisionCheck();

	float Position(float a_x, float a_y);
};

#endif