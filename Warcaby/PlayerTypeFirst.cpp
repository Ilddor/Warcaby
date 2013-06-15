#include "PlayerTypeFirst.h"
#include <string>
#include <iostream>
#include "Misc.h"
#include <Windows.h>

CPiece* CPlayerTypeFirst::getPieceToMove()
{
	CPiece* tmp = nullptr;
	for(auto& it = m_gamePtr->getBoard().begin(); it != m_gamePtr->getBoard().end(); ++it)
	{
		if((*it)->getColor() == m_color)
		{
			if(tmp == nullptr)
				tmp = (*it);
			else
			{
				if(m_color == BLACK)
				{
					if((*it)->getPosition().x > tmp->getPosition().x)
					{
						tmp = (*it);
					}
				}
				else
				{
					if((*it)->getPosition().x < tmp->getPosition().x)
					{
						tmp = (*it);
					}	
				}
			}
		}	
	}
	return tmp; 	
}

sf::Vector2f CPlayerTypeFirst::findBeatingMove(CPiece* piece)
{
	sf::Vector2f pos = piece->getPosition();
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
}

void CPlayerTypeFirst::update()
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
		
		CMove* move = nullptr;
		CPiece* piece = nullptr;
		sf::Vector2f beatingMove;
		do
		{
			piece = getPieceToMove();
			beatingMove = findBeatingMove(piece);
			if(beatingMove != piece->getPosition())
				move = new CMove(piece->getPosition().x/100, piece->getPosition().y/100, beatingMove.x/100, beatingMove.y/100, false, false);
			else
			{
				if(m_color == BLACK)
				{
					if(piece->getPosition().y)
					{

					}
				}
				else
				{
					//W lewo
				}
			}
			//move = new CMove((*it)->getPosition().x/100, (*it)->getPosition().y/100, dst.x/100, dst.y/100, false, false);
		}
		while(!makeMove(*move));
	}
	if(eventName == "gameEnd")
	{
		std::cout << "GG WP" << std::endl;
	}
	if(eventName == "playerMove")
	{
		std::cout << "Hey! Think faster!" << std::endl;
	}
	if(eventName == "draw")
	{
		std::cout << "Dayuuuuum! A draw ;-( " << std::endl;
	}
	if(eventName == "gameStart")
	{
		std::cout << "I\'m gonna rip your head off and piss into your neck!" << std::endl;
	}
}

void CPlayerTypeFirst::addGamePtr(CGame* ptr)
{
	m_gamePtr = ptr;
}

void CPlayerTypeFirst::setColor(EPieceColor color)
{
	m_color = color;
}

bool CPlayerTypeFirst::makeMove(CMove move)
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

CPlayerTypeFirst::CPlayerTypeFirst(void)
{
}


CPlayerTypeFirst::~CPlayerTypeFirst(void)
{
}
