#pragma once

#include <list>
#include <string>
#include "Set.h"

class CBotMemory
{
private:
	std::list<CSet*> m_memory;
public:
	void addMoveToLastSet(int srcx, int srcy, int dstx, int dsty, bool winning, bool color);
	void addSet(const std::vector<CPiece*>& board);

	void setWinner(EPieceColor color);	//use it on main memory and I will cut off your balls

	CMove* findSet(const std::vector<CPiece*>& board);

	void saveToFile(std::string path);
	void loadFromFile(std::string path);

	void merge(CBotMemory& other);
	CBotMemory(void);
	~CBotMemory(void);
};

