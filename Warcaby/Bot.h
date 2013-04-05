#pragma once
#include "Misc.h"
#include <string>

class CBot
{
private:
	EPieceColor m_color;
public:
	void update(std::string eventName, EPieceColor color);
	CBot(void);
	~CBot(void);
};