#include "Set.h"

void CSet::addMove(int srcx, int srcy, int dstx, int dsty, bool winning, bool color)
{
	m_moves.push_back(new CMove(srcx, srcy, dstx, dsty, winning, color));
}

CSet::CSet(const std::vector<CPiece*>& board)
{
	m_part1 = m_part2 = m_part3 = 0;
	sf::Vector2i pos;
	for(auto it = board.begin(); it != board.end(); ++it)
	{
		pos.x = (*it)->getPosition().x/2.f;
		pos.y = (*it)->getPosition().y;
		pos /= 100;
		m_part1 |= 1<<((pos.y*4)+pos.x);
		if(pos.y < 4)
		{
			if((*it)->getColor() == EPieceColor::WHITE)
				m_part2 |= 1<<(((pos.y*4)+pos.x)*2);
			if((*it)->isKing())
				m_part2 |= 1<<((((pos.y*4)+pos.x)*2)+1);
		}
		else
		{
			if((*it)->getColor() == EPieceColor::WHITE)
				m_part3 |= 1<<((((pos.y*4)+pos.x)*2)-32);
			if((*it)->isKing())
				m_part3 |= 1<<(((((pos.y*4)+pos.x)*2)-32)+1);
		}
	}
}

CSet::CSet(void)
{
}


CSet::~CSet(void)
{
}
