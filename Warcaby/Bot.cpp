#include "Bot.h"
#include <string>
#include <iostream>
#include "Misc.h"
#include <Windows.h>

sf::Vector2f CBot::findBeatingMove(CPiece* piece)
{
	sf::Vector2f pos = piece->getPosition();

	/*if(!piece->isKing())
	{
		if(m_gamePtr->isMovePossible(piece->getPosition() + sf::Vector2f(200,200), piece))
			return piece->getPosition() + sf::Vector2f(200,200);

		if(m_gamePtr->isMovePossible(piece->getPosition() + sf::Vector2f(-200,200), piece))
			return piece->getPosition() + sf::Vector2f(-200,200);

		if(m_gamePtr->isMovePossible(piece->getPosition() + sf::Vector2f(-200,-200), piece))
			return piece->getPosition() + sf::Vector2f(-200,-200);

		if(m_gamePtr->isMovePossible(piece->getPosition() + sf::Vector2f(200,-200), piece))
			return piece->getPosition() + sf::Vector2f(200,-200);
	}
	else
	{*/
		for(auto it = m_gamePtr->getBoard().begin(); it != m_gamePtr->getBoard().end(); ++it)
		{
			if((*it)->getPosition() != piece->getPosition() && (*it)->getColor() != piece->getColor())
			{
				if(abs(((*it)->getPosition() - pos).x) == abs(((*it)->getPosition() - pos).y))
				{
					sf::Vector2f dir(((*it)->getPosition() - pos).x/(abs(((*it)->getPosition() - pos).x)/100),
								((*it)->getPosition() - pos).y/(abs(((*it)->getPosition() - pos).y)/100));
					if(((*it)->getPosition() + dir).x < 0 ||
					   ((*it)->getPosition() + dir).x > 700 ||
					   ((*it)->getPosition() + dir).y < 0 ||
					   ((*it)->getPosition() + dir).y > 700)
						continue;
					if(m_gamePtr->isMovePossible((*it)->getPosition() + dir, piece))
						return (*it)->getPosition() + dir;
				}
			}
		}
	//}
}

void CBot::update()
{
	std::string eventName = m_gamePtr->getLastEvent();
	EPieceColor color = m_gamePtr->getMoveFor();


	if(eventName == "turn" && m_color == color)
	{
		std::cout << "I think I should make a move now" << std::endl;
		
		CMove* move;// = m_mainMemory.findSet(m_gamePtr->getBoard());
		/*if(move == nullptr)
		{
			std::cout << "Oops! I don't know what to do:(" << std::endl;

		}
		else
			std::cout << "Yeah! I know what to do!" << std::endl;

		if(move != nullptr)
		{
			while(!makeMove(*move))
			{
			}
		}*/

		do
		{
			move = m_mainMemory.findSet(m_gamePtr->getBoard());
			if(move == nullptr)
			{
				if(m_gamePtr->checkIfBeating())
				{
					for(auto it = m_gamePtr->getBoard().begin(); it != m_gamePtr->getBoard().end(); ++it)
					{
						if(m_color == (*it)->getColor() && m_gamePtr->isBeatingPossible(*it))
						{
							sf::Vector2f dst(findBeatingMove(*it));
							move = new CMove((*it)->getPosition().x/100, (*it)->getPosition().y/100, dst.x/100, dst.y/100, false, false); // in this case winning and color in CMove doesn't matter, we only need to pass coordinates
							break;
						}
					}
				}
			}
		}
		while(!makeMove(*move));
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

bool CBot::makeMove(CMove move)
{
	int srcx = (move.getSource() & 0x0f);
	int srcy = (move.getSource() & 0xf0)>>4;

	int dstx = (move.getDestination() & 0x0f);
	int dsty = (move.getDestination() & 0xf0)>>4;

	m_gamePtr->selectPiece(srcx*100, srcy*100);
	if(m_gamePtr->moveSelectedPiece(dstx*100, dsty*100))
	{
		m_gamePtr->changeTurn();
		m_gamePtr->clearSelect();
		return true;
	}
	return false;
}

CBot::CBot(void)
{
	m_mainMemory.loadFromFile("data.xml");
}


CBot::~CBot(void)
{
	m_mainMemory.saveToFile("data.xml");
}
