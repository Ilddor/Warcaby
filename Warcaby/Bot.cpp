#include "Bot.h"
#include <string>
#include <iostream>
#include "Misc.h"

void CBot::update()
{
	std::string eventName = m_gamePtr->getLastEvent();
	EPieceColor color = m_gamePtr->getMoveFor();


	if(eventName == "turn" && m_color == color)
	{
		std::cout << "I think I should make a move now" << std::endl;
		//Here we proceed with magic such as getting board, thinking of best move and killing the other motherfucker
	}
	if(eventName == "gameEnd")
	{
		if(color == EPieceColor::WHITE)
			m_tmpMemory.addMoveToLastSet(m_gamePtr->getLastMoveSrc().x, m_gamePtr->getLastMoveSrc().y, m_gamePtr->getLastMoveDst().x, m_gamePtr->getLastMoveDst().y, false, true);
		else
			m_tmpMemory.addMoveToLastSet(m_gamePtr->getLastMoveSrc().x, m_gamePtr->getLastMoveSrc().y, m_gamePtr->getLastMoveDst().x, m_gamePtr->getLastMoveDst().y, false, false);

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
			m_tmpMemory.addMoveToLastSet(m_gamePtr->getLastMoveSrc().x, m_gamePtr->getLastMoveSrc().y, m_gamePtr->getLastMoveDst().x, m_gamePtr->getLastMoveDst().y, false, true);
		else
			m_tmpMemory.addMoveToLastSet(m_gamePtr->getLastMoveSrc().x, m_gamePtr->getLastMoveSrc().y, m_gamePtr->getLastMoveDst().x, m_gamePtr->getLastMoveDst().y, false, false);

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


CBot::CBot(void)
{
	m_mainMemory.loadFromFile("data.xml");
}


CBot::~CBot(void)
{
	m_mainMemory.saveToFile("data.xml");
}
