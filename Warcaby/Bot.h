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
public:
	void update();

	void addGamePtr(CGame* ptr);

	void setColor(EPieceColor color);
	void makeMove(CMove move);

	CBot(void);
	~CBot(void);
};