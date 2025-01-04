#pragma once
//#include <stdlib.h>
#include <random>

#define CANVAS_WIDTH 28.0f
#define CANVAS_HEIGHT 16.0f

#define ASSET_PATH "./assets/"


#define SETCOLOR(c, r, g, b) do { c[0] = r; c[1] = g; c[2] = b; } while(0)



#define RANDOTO1()(rand()/(float)RAND_MAX)


struct Disk
{
	float cx, cy;
	float radius;

};

