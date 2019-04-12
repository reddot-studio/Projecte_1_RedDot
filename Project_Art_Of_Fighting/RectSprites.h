#ifndef __RectSprites_H__
#define __RectSprites_H__
#include "p2Point.h"
#include "SDL/include/SDL_rect.h"

class RectSprites {

public:
	SDL_Rect rect;
	iPoint offset;
	iPoint displacement;


public:
	RectSprites() {};
	RectSprites(SDL_Rect rect, iPoint point, iPoint displ) : rect(rect), offset(point), displacement(displ){}
	void SetOffset(int x,int y) {
		offset.x += x;
		offset.y += y;
	}

	void SetDisplacement(int x, int y) 
	{
		displacement.x += x;
		displacement.y += y;
	}

};

#endif // !__RectSprites_H__
