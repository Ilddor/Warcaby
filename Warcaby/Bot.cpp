#include "Bot.h"
#include <string>
#include <iostream>
#include "Misc.h"
#include <Windows.h>

void CBot::update()
{
	std::string eventName = m_gamePtr->getLastEvent();
	EPieceColor color = m_gamePtr->getMoveFor();


	if(eventName == "turn" && m_color == color)
	{
		std::cout << "I think I should make a move now" << std::endl;
		
		CMove* move = m_mainMemory.findSet(m_gamePtr->getBoard());
		if(move == nullptr)
			std::cout << "Oops! I don't know what to do:(" << std::endl;
		else
			std::cout << "Yeah! I know what to do!" << std::endl;

		if(move != nullptr)
			makeMove(*move);
	}
	if(eventName == "gameEnd")
	{
		if(color == EPieceColor::WHITE)
			m_tmpMemory.addMoveToLastSet(m_gamePtr->getLastMoveSrc().x/100, m_gamePtr->getLastMoveSrc().y/100, m_gamePtr->getLastMoveDst().x/100, m_gamePtr->getLastMoveDst().y/100, false, true);
		else
			m_tmpMemory.addMoveToLastSet(m_gamePtr->getLastMoveSrc().x/100, m_gamePtr->getLastMoveSrc().y/100, m_gamePtr->getLastMoveDst().x/100, m_gamePtr->getLastMoveDst().y/100, false, false);

		m_tmpMemory.setWinner(color);
		if(m_color == color)
		{
			std::cout << "Yippie!" << std::endl;
			//Here we will boast about how we just killed that motherfucker
		}
		else
		{
		  	std::cout << "Well shit :(" << std::endl;
			//Here we will cry like a little girl and get suicidal thoughts ;-)
		}
		m_mainMemory.merge(m_tmpMemory);
	}
	if(eventName == "playerMove")
	{
		if(color == EPieceColor::WHITE)
			m_tmpMemory.addMoveToLastSet(m_gamePtr->getLastMoveSrc().x/100, m_gamePtr->getLastMoveSrc().y/100, m_gamePtr->getLastMoveDst().x/100, m_gamePtr->getLastMoveDst().y/100, false, true);
		else
			m_tmpMemory.addMoveToLastSet(m_gamePtr->getLastMoveSrc().x/100, m_gamePtr->getLastMoveSrc().y/100, m_gamePtr->getLastMoveDst().x/100, m_gamePtr->getLastMoveDst().y/100, false, false);

		m_tmpMemory.addSet(m_gamePtr->getBoard());
	}
	if(eventName == "draw")
	{
		m_mainMemory.merge(m_tmpMemory);
	}
	if(eventName == "gameStart" && color != m_color)
	{
		m_tmpMemory.addSet(m_gamePtr->getBoard());
	}
}

void CBot::addGamePtr(CGame* ptr)
{
	m_gamePtr = ptr;
}

void CBot::setColor(EPieceColor color)
{
	m_color = color;
}

void CBot::makeMove(CMove move)
{
	int srcx = (move.getSource() & 0x0f);
	int srcy = (move.getSource() & 0xf0)>>4;

	int dstx = (move.getDestination() & 0x0f);
	int dsty = (move.getDestination() & 0xf0)>>4;

	m_gamePtr->selectPiece(srcx*100, srcy*100);
	if(m_gamePtr->moveSelectedPiece(dstx*100, dsty*100))
		m_gamePtr->changeTurn();
	m_gamePtr->clearSelect();
}

CBot::CBot(void)
{
	m_mainMemory.loadFromFile("data.xml");
}


CBot::~CBot(void)
{
	m_mainMemory.saveToFile("data.xml");
}
