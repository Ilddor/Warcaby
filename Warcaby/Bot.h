#pragma once
#include "Misc.h"
#include "BotMemory.h"
#include "Listener.h"
#include <string>

class CBot:
	public Listener
{
private:
	EPieceColor m_color;

	CBotMemory m_mainMemory;
	CBotMemory m_tmpMemory;
public:
	void update();
	CBot(void);
	~CBot(void);
};