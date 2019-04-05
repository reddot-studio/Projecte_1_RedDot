#ifndef __RectSprites_H__
#define __RectSprites_H__
#include "p2Point.h"
#include "SDL/include/SDL_rect.h"

class RectSprites {

public:
	SDL_Rect rect;
	iPoint offset;


public:
	RectSprites() {};
	RectSprites(SDL_Rect rect, iPoint point) : rect(rect), offset(point){}
	void SetOffset(int x,int y) {
		offset.x += x;
		offset.y += y;
	}

};

#endif // !__RectSprites_H__
