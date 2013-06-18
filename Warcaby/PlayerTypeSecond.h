#pragma once

#include <string>

#include "Misc.h"
#include "BotMemory.h"
#include "Listener.h"
#include "Game.h"

class CPlayerTypeSecond:
	public Listener
{
private:
	EPieceColor m_color;

	CGame* m_gamePtr;

	sf::Vector2f findBeatingMove(CPiece* piece);
	CPiece* getRandomPiece();
	CMove* findNonBeatingMove();
	bool isMoveValid(const sf::Vector2f& src, const sf::Vector2f& dst);
	void myTurn();
public:
	void update();

	void addGamePtr(CGame* ptr);

	void setColor(EPieceColor color);
	bool makeMove(CMove* move);

	CPlayerTypeSecond(void);
	~CPlayerTypeSecond(void);
};