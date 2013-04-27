#include "Bot.h"
#include <string>
#include <iostream>
#include "Misc.h"
#include <Windows.h>

bool CBot::randomDecision()
{
	return (rand()%100)<30;
}

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

CMove* CBot::findNonBeatingMove(bool lookForSafety, bool random)
{
	for(auto it = m_gamePtr->getBoard().begin(); it != m_gamePtr->getBoard().end(); ++it)
	{
		if(m_color == (*it)->getColor())
		{
			if(m_gamePtr->isMovePossible((*it)->getPosition() + sf::Vector2f(100,100), *it))
			{
				sf::Vector2f dst((*it)->getPosition() + sf::Vector2f(100,100));
				if(dst.x >= 0 && dst.x < 800 && dst.y >= 0 && dst.y < 800 && (lookForSafety? !isPositionDangerous(dst, (*it)->getPosition()):true) && (random? randomDecision():true))
				{
					return new CMove((*it)->getPosition().x/100, (*it)->getPosition().y/100, dst.x/100, dst.y/100, false, false);	// in this case winning and color in CMove doesn't matter, we only need to pass coordinates
				}
			}
			if(m_gamePtr->isMovePossible((*it)->getPosition() + sf::Vector2f(-100,100), *it))
			{
				sf::Vector2f dst((*it)->getPosition() + sf::Vector2f(-100,100));
				if(dst.x >= 0 && dst.x < 800 && dst.y >= 0 && dst.y < 800 && (lookForSafety? !isPositionDangerous(dst, (*it)->getPosition()):true) && (random? randomDecision():true))
				{
					return new CMove((*it)->getPosition().x/100, (*it)->getPosition().y/100, dst.x/100, dst.y/100, false, false);	// in this case winning and color in CMove doesn't matter, we only need to pass coordinates
				}
			}
			if(m_gamePtr->isMovePossible((*it)->getPosition() + sf::Vector2f(-100,-100), *it))
			{
				sf::Vector2f dst((*it)->getPosition() + sf::Vector2f(-100,-100));
				if(dst.x >= 0 && dst.x < 800 && dst.y >= 0 && dst.y < 800 && (lookForSafety? !isPositionDangerous(dst, (*it)->getPosition()):true) && (random? randomDecision():true))
				{
					return new CMove((*it)->getPosition().x/100, (*it)->getPosition().y/100, dst.x/100, dst.y/100, false, false);	// in this case winning and color in CMove doesn't matter, we only need to pass coordinates
				}
			}
			if(m_gamePtr->isMovePossible((*it)->getPosition() + sf::Vector2f(100,-100), *it))
			{
				sf::Vector2f dst((*it)->getPosition() + sf::Vector2f(100,-100));
				if(dst.x >= 0 && dst.x < 800 && dst.y >= 0 && dst.y < 800 && (lookForSafety? !isPositionDangerous(dst, (*it)->getPosition()):true) && (random? randomDecision():true))
				{
					return new CMove((*it)->getPosition().x/100, (*it)->getPosition().y/100, dst.x/100, dst.y/100, false, false);	// in this case winning and color in CMove doesn't matter, we only need to pass coordinates
				}
			}
		}
	}
	return nullptr;
}

bool CBot::isPositionDangerous(sf::Vector2f pos, sf::Vector2f src)
{
	sf::Vector2f dir(100,100);
	if((pos+dir).x >= 0 && (pos+dir).x < 800 && (pos+dir).y >= 0 && (pos+dir).y < 800 &&
		(pos-dir).x >= 0 && (pos-dir).x < 800 && (pos-dir).y >= 0 && (pos-dir).y < 800)
	{
		bool minus = false, plus = false;
		bool color = false;
		for(auto it = m_gamePtr->getBoard().begin(); it != m_gamePtr->getBoard().end(); ++it)
		{
			if((*it)->getPosition() != src)
			{
				if((*it)->getPosition() == pos - dir)
				{
					minus = true;
					if((*it)->getColor() != m_color)
						color = true;
				}
			}
		}
		for(auto it = m_gamePtr->getBoard().begin(); it != m_gamePtr->getBoard().end(); ++it)
		{
			if((*it)->getPosition() != pos)
			{
				if((*it)->getPosition() == pos - dir)
				{
					plus = true;
					if((*it)->getColor() != m_color)
						color = true;
				}
			}
		}
		if(minus != plus && color)
			return true;
	}
	else
		return false;

	dir = sf::Vector2f(-100,100);
	if((pos+dir).x >= 0 && (pos+dir).x < 800 && (pos+dir).y >= 0 && (pos+dir).y < 800 &&
		(pos-dir).x >= 0 && (pos-dir).x < 800 && (pos-dir).y >= 0 && (pos-dir).y < 800)
	{
		bool minus = false, plus = false;
		bool color = false;
		for(auto it = m_gamePtr->getBoard().begin(); it != m_gamePtr->getBoard().end(); ++it)
		{
			if((*it)->getPosition() != pos)
			{
				if((*it)->getPosition() == pos - dir)
				{
					minus = true;
					if((*it)->getColor() != m_color)
						color = true;
				}
			}
		}
		for(auto it = m_gamePtr->getBoard().begin(); it != m_gamePtr->getBoard().end(); ++it)
		{
			if((*it)->getPosition() != pos)
			{
				if((*it)->getPosition() == pos - dir)
				{
					plus = true;
					if((*it)->getColor() != m_color)
						color = true;
				}
			}
		}
		if(minus != plus && color)
			return true;
	}
	else
		return false;
}

void CBot::update()
{
	m_gamePtr->getWindow().clear();
	m_gamePtr->drawBackground(m_gamePtr->getWindow());
	m_gamePtr->drawPieces(m_gamePtr->getWindow());
	m_gamePtr->getWindow().display();

	std::string eventName = m_gamePtr->getLastEvent();
	EPieceColor color = m_gamePtr->getMoveFor();


	if(eventName == "turn" && m_color == color)
	{
		std::cout << "I think I should make a move now" << std::endl;
		
		CMove* move = nullptr;// = m_mainMemory.findSet(m_gamePtr->getBoard());
		/*if(move == nullptr)
			std::cout << "Oops! I don't know what to do:(" << std::endl;
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
			if(move != nullptr)
			{
				//delete move;
				move = nullptr;
			}
			move = m_mainMemory.findSet(m_gamePtr->getBoard());
			if(randomDecision())
			{
				delete move;
				move == nullptr;
			}
			if(move == nullptr)
			{
				std::cout << "Oops! I don't know what to do:( YOLO!" << std::endl;
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
				else
				{
					move = findNonBeatingMove(true, true);
					if(move == nullptr)
					{
						move = findNonBeatingMove(true, false);
						if(move == nullptr)
						{
							move = findNonBeatingMove(false, true);
							if(move == nullptr)
								move = findNonBeatingMove(false, false);
						}
					}
				}
			}
			else
				std::cout << "Yeah! I know what to do!" << std::endl;
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
		if(m_merged == false)
		{
			m_mainMemory.merge(m_tmpMemory);
			m_merged = true;
		}
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
		if(m_merged == false)
		{
			m_mainMemory.merge(m_tmpMemory);
			m_merged = true;
		}
	}
	if(eventName == "gameStart")
	{
		m_tmpMemory.addSet(m_gamePtr->getBoard());
		m_merged = false;
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

	if(m_gamePtr->selectPiece(srcx*100, srcy*100))
	{
		if(m_gamePtr->moveSelectedPiece(dstx*100, dsty*100))
		{
			m_gamePtr->changeTurn();
			m_gamePtr->clearSelect();
			return true;
		}
	}
	return false;
}

CBot::CBot(void)
{
	m_mainMemory.loadFromFile("data.xml");
	m_merged = false;
}


CBot::~CBot(void)
{
	m_mainMemory.saveToFile("data.xml");
}
