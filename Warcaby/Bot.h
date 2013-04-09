#pragma once

#include <string>

#include "Misc.h"
#include "BotMemory.h"
#include "Listener.h"
#include "Game.h"

class CBot:
	public Listener
{
private:
	EPieceColor m_color;

	CGame* m_gamePtr;

	CBotMemory m_mainMemory;
	CBotMemory m_tmpMemory;

	sf::Vector2f findBeatingMove(CPiece* piece);
	CMove* findNonBeatingMove();
public:
	void update();

	void addGamePtr(CGame* ptr);

	void setColor(EPieceColor color);
	bool makeMove(CMove move);

	CBot(void);
	~CBot(void);
};