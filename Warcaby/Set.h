#pragma once

#include <list>
#include "Piece.h"
#include "Move.h"

class CSet
{
private:
	int m_part1;			//part1 describes what fields on board are filled or not(each bit is responsible for one field)
	int m_part2, m_part3;	//if certain field is filled part2 and part3 describe what type od piece is there
						//2bits for each field (upper half of board part2, bottom half = part3)
						//one bit describe if it's king or not(king = 1), second if its white or black(white = 1)
	std::list<CMove*> m_moves;

	CSet(void);
public:
	void addMove(int srcx, int srcy, int dstx, int dsty, bool winning, bool color);

	CSet(const std::vector<CPiece*>& board);
	~CSet(void);
};

