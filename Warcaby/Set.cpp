#include "Set.h"

const std::list<CMove*>& CSet::getMoves()
{
	return m_moves;
}

int CSet::getPart1()
{
	return m_part1;
}

int CSet::getPart2()
{
	return m_part2;
}

int CSet::getPart3()
{
	return m_part3;
}

void CSet::setColorWinning(bool color)
{
	for(auto it = m_moves.begin(); it != m_moves.end(); ++it)
	{
		if(color == (*it)->getColor())
			(*it)->setWinning();
	}
}

void CSet::addMove(char src, char dst, char info)
{
	m_moves.push_back(new CMove(src, dst, info));
}

void CSet::addMove(int srcx, int srcy, int dstx, int dsty, bool winning, bool color)
{
	m_moves.push_back(new CMove(srcx, srcy, dstx, dsty, winning, color));
}

void CSet::MergeMoves(CSet& other)
{
	//m_moves.merge(other.m_moves);
	m_moves.insert(m_moves.end(), other.getMoves().begin(), other.getMoves().end());
	m_moves.unique([](CMove* a, CMove* b)->bool{
		if((a->getSource() == b->getSource()) &&
			(a->getDestination() == b->getDestination()) &&
			(a->getInfo() == b->getInfo()))					//check if move has the same parameters (winning doesnt matter)
			return true;
		else
			return false;
	});
}

CSet::CSet(int part1, int part2, int part3)
{
	m_part1 = part1;
	m_part2 = part2;
	m_part3 = part3;
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
	for(auto it = m_moves.begin(); it != m_moves.end(); ++it)
	{
		//delete(*it);
	}
	m_moves.clear();
}
