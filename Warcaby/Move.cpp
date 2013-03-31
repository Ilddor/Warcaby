#include "Move.h"

CMove::CMove(int srcx, int srcy, int dstx, int dsty, bool winning, bool color)
{
	source = destination = info = 0;
	source |= srcx;
	source |= srcy<<4;
	destination |= dstx;
	destination |= dsty<<4;
	if(winning)
		info |= 1<<0;
	if(color)
		info |= 1<<1;
}

CMove::CMove(void)
{
}


CMove::~CMove(void)
{
}
