#include "PlayerTypeSecond.h"
#include <string>
#include <iostream>
#include "Misc.h"
#include <Windows.h>

bool CPlayerTypeSecond::isMoveValid(const sf::Vector2f& src, const sf::Vector2f& dst)
{
	if(dst.x/100 >= 0 && dst.x/100 <= 7 && dst.y/100 >= 0 && dst.y/100 <= 7)
		return true;
	else
		return false;
}

CPiece* CPlayerTypeSecond::getRandomPiece()
{
	std::list<CPiece*> piecesPool;
	for(auto& it = m_gamePtr->getBoard().begin(); it != m_gamePtr->getBoard().end(); ++it)
	{
		if((*it)->getColor() == m_color)
		{
			if(m_gamePtr->isMovePossible(sf::Vector2f((*it)->getPosition().x + 100, (*it)->getPosition().y + 100), (*it)))
				piecesPool.push_back((*it));
			else if(m_gamePtr->isMovePossible(sf::Vector2f((*it)->getPosition().x - 100, (*it)->getPosition().y + 100), (*it)))
				piecesPool.push_back((*it));
			else if(m_gamePtr->isMovePossible(sf::Vector2f((*it)->getPosition().x + 100, (*it)->getPosition().y - 100), (*it)))
				piecesPool.push_back((*it)); 
			else if(m_gamePtr->isMovePossible(sf::Vector2f((*it)->getPosition().x - 100, (*it)->getPosition().y - 100), (*it)))
				piecesPool.push_back((*it));  
		}
	}
	int randPiece = rand()%piecesPool.size();
	int actualPieceNumber = 0;
	CPiece* randedPiece = nullptr;
	for(auto& it = piecesPool.begin(); it != piecesPool.end(); it++)
	{
		if(actualPieceNumber == randPiece)
		{
			randedPiece = (*it);
			break;	
		}
		else
			actualPieceNumber++;
	}
	return randedPiece;
}

sf::Vector2f CPlayerTypeSecond::findBeatingMove(CPiece* piece)
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

CMove* CPlayerTypeSecond::findNonBeatingMove()
{
	for(auto it = m_gamePtr->getBoard().begin(); it != m_gamePtr->getBoard().end(); ++it)
	{
		if(m_color == (*it)->getColor())
		{
			if(m_gamePtr->isMovePossible((*it)->getPosition() + sf::Vector2f(100,100), *it))
			{
				sf::Vector2f dst((*it)->getPosition() + sf::Vector2f(100,100));
				if(dst.x >= 0 && dst.x < 800 && dst.y >= 0 && dst.y < 800)
				{
					return new CMove((*it)->getPosition().x/100, (*it)->getPosition().y/100, dst.x/100, dst.y/100, false, false);	// in this case winning and color in CMove doesn't matter, we only need to pass coordinates
				}
			}
			if(m_gamePtr->isMovePossible((*it)->getPosition() + sf::Vector2f(-100,100), *it))
			{
				sf::Vector2f dst((*it)->getPosition() + sf::Vector2f(-100,100));
				if(dst.x >= 0 && dst.x < 800 && dst.y >= 0 && dst.y < 800)
				{
					return new CMove((*it)->getPosition().x/100, (*it)->getPosition().y/100, dst.x/100, dst.y/100, false, false);	// in this case winning and color in CMove doesn't matter, we only need to pass coordinates
				}
			}
			if(m_gamePtr->isMovePossible((*it)->getPosition() + sf::Vector2f(-100,-100), *it))
			{
				sf::Vector2f dst((*it)->getPosition() + sf::Vector2f(-100,-100));
				if(dst.x >= 0 && dst.x < 800 && dst.y >= 0 && dst.y < 800)
				{
					return new CMove((*it)->getPosition().x/100, (*it)->getPosition().y/100, dst.x/100, dst.y/100, false, false);	// in this case winning and color in CMove doesn't matter, we only need to pass coordinates
				}
			}
			if(m_gamePtr->isMovePossible((*it)->getPosition() + sf::Vector2f(100,-100), *it))
			{
				sf::Vector2f dst((*it)->getPosition() + sf::Vector2f(100,-100));
				if(dst.x >= 0 && dst.x < 800 && dst.y >= 0 && dst.y < 800)
				{
					return new CMove((*it)->getPosition().x/100, (*it)->getPosition().y/100, dst.x/100, dst.y/100, false, false);	// in this case winning and color in CMove doesn't matter, we only need to pass coordinates
				}
			}
		}
	}
	return nullptr;
}

void CPlayerTypeSecond::myTurn()
{
	std::cout << "I think I should make a move now" << std::endl;
	
	CMove* move = nullptr;
	do
	{
		if(move != nullptr)
		{
			//delete move;
			move = nullptr;
		}
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
			else
			{
				move = findNonBeatingMove();
			}
		}
	}
	while(!makeMove(move));
}
void CPlayerTypeSecond::update()
{
	m_gamePtr->getWindow().clear();
	m_gamePtr->drawBackground(m_gamePtr->getWindow());
	m_gamePtr->drawPieces(m_gamePtr->getWindow());
	m_gamePtr->getWindow().display();

	std::string eventName = m_gamePtr->getLastEvent();
	EPieceColor color = m_gamePtr->getMoveFor();


	if(eventName == "turn" && m_color == color)
	{
		myTurn();
	}
	if(eventName == "gameEnd")
	{
		std::cout << "GG WP" << std::endl;
	}
	if(eventName == "playerMove")
	{
		std::cout << "MOVE FASTER!" << std::endl;
	}
	if(eventName == "draw")
	{
		std::cout << "Boo!" << std::endl;
	}
	if(eventName == "gameStart")
	{
		std::cout << "Lets roll" << std::endl;
		myTurn();
	}
}

void CPlayerTypeSecond::addGamePtr(CGame* ptr)
{
	m_gamePtr = ptr;
}

void CPlayerTypeSecond::setColor(EPieceColor color)
{
	m_color = color;
}

bool CPlayerTypeSecond::makeMove(CMove* move)
{
	bool returnedValue = false;
	if(move != nullptr)
	{
		int srcx = (move->getSource() & 0x0f);
		int srcy = (move->getSource() & 0xf0)>>4;

		int dstx = (move->getDestination() & 0x0f);
		int dsty = (move->getDestination() & 0xf0)>>4;

		if(m_gamePtr->selectPiece(srcx*100, srcy*100))
		{
			if(m_gamePtr->moveSelectedPiece(dstx*100, dsty*100))
			{
				m_gamePtr->changeTurn();
				m_gamePtr->clearSelect();
				returnedValue = true;
			}
		}
		delete move;
		move = nullptr;
	}
	return returnedValue;
}

CPlayerTypeSecond::CPlayerTypeSecond(void)
{
}


CPlayerTypeSecond::~CPlayerTypeSecond(void)
{
}
