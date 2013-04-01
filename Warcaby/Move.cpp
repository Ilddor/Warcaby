#include "Move.h"

void CMove::setWinning()
{
	m_info |= 1<<0;
}

bool CMove::getColor()
{
	if(m_info & 1<<1)
		return true;
	else
		return false;
}

CMove::CMove(char src, char dst, char info)
{
	m_source = src;
	m_destination = dst;
	m_info = info;
}

CMove::CMove(int srcx, int srcy, int dstx, int dsty, bool winning, bool color)
{
	m_source = m_destination = m_info = 0;
	m_source |= srcx;
	m_source |= srcy<<4;
	m_destination |= dstx;
	m_destination |= dsty<<4;
	if(winning)
		m_info |= 1<<0;
	if(color)
		m_info |= 1<<1;
}

CMove::CMove(void)
{
}


CMove::~CMove(void)
{
}
