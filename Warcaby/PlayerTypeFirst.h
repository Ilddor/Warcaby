#pragma once

#include <string>

#include "Misc.h"
#include "BotMemory.h"
#include "Listener.h"
#include "Game.h"

class CPlayerTypeFirst:
	public Listener
{
private:
	EPieceColor m_color;

	CGame* m_gamePtr;

	bool randomDecision();
	sf::Vector2f findBeatingMove(CPiece* piece); 
	CPiece* getPieceToMove(); //Get most left piece (from his point of view)
public:
	void update();

	void addGamePtr(CGame* ptr);

	void setColor(EPieceColor color);
	bool makeMove(CMove move);

	CPlayerTypeFirst(void);
	~CPlayerTypeFirst(void);
};