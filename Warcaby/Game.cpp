#include "Game.h"
#include <iostream>

void CGame::mousePressed(sf::Event& event)
{
	if(event.mouseButton.x < 0 || event.mouseButton.x >= 800 || event.mouseButton.y < 0 || event.mouseButton.y >= 799)
		return;
	if(m_selected == nullptr)
	{
		bool beatingPossible = checkIfBeating();
		if(event.mouseButton.button == sf::Mouse::Left && m_moveFor == m_playerColor)
		{
			for(auto it = m_Pieces.begin(); it != m_Pieces.end(); ++it)
			{
				if((*it)->pressedOn(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					if((*it)->getColor() == m_playerColor)
					{
						if(!beatingPossible || isBeatingPossible(*it))
						{
							m_selected = (*it);
							m_selected->setSelected(true);
						}
					}
				}
			}
		}
	}
	else
	{
		if(m_backgroud.getPixel(event.mouseButton.x, event.mouseButton.y) == sf::Color(40, 40, 40))
		{
			if(isMovePossible(sf::Vector2f(event.mouseButton.x-event.mouseButton.x%100, event.mouseButton.y-event.mouseButton.y%100), m_selected))	//check if requested move is possible
			{
				sf::Vector2f newpos(event.mouseButton.x-event.mouseButton.x%100, event.mouseButton.y-event.mouseButton.y%100);
				sf::Vector2f prevpos(m_selected->getPosition());
				bool normalMove = true;
				if(abs(newpos.x - prevpos.x) >= 200)	//if the move was over 2 fields or more -> delete skipped piece
				{
					if(!m_selected->isKing())
					{
						sf::Vector2f erasePos;			//vector to subtract from new pos(for kings compatibility)
						if(newpos.x - prevpos.x > 0)
							erasePos.x = 100;
						else
							erasePos.x = -100;

						if(newpos.y - prevpos.y > 0)
							erasePos.y = 100;
						else
							erasePos.y = -100;

						for(auto it = m_Pieces.begin(); it != m_Pieces.end(); ++it)
						{
							if((*it)->getPosition() == newpos-erasePos)
							{
								m_Pieces.erase(it);
								normalMove = false;
								break;
							}
						}
					}
					else
					{
						sf::Vector2f gap((newpos - prevpos).x/(abs((newpos - prevpos).x)/100), (newpos - prevpos).y/(abs((newpos - prevpos).y)/100));
						sf::Vector2f erasePos = prevpos + gap;

						while(erasePos != newpos)
						{
							for(auto it = m_Pieces.begin(); it != m_Pieces.end(); ++it)
							{
								if((*it)->getPosition() == erasePos)
								{
									m_Pieces.erase(it);
									normalMove = false;
									break;
								}
							}
							erasePos += gap;
						}
					}
				}

				if(abs(newpos.x - prevpos.x) >= 200 || !m_multiBeating)
				//if(!m_multiBeating)
				{
					m_selected->setPosition(newpos);

					if(m_moveFor == EPieceColor::WHITE)
						mem.addMoveToLastSet(prevpos.x, prevpos.y, newpos.x, newpos.y, false, true);
					else
						mem.addMoveToLastSet(prevpos.x, prevpos.y, newpos.x, newpos.y, false, false);

					checkForKings();
				}

				if(isBeatingPossible(m_selected) && !normalMove)
				{											//if beated something check if there is possibiliy to multibeat
					m_multiBeating = true;
					return;
				}
				else	//if not, change movefor
				{
					changeTurn();
					m_multiBeating = false;
				}
			}
			else
			{
				/*if(m_multiBeating)
				{
					changeTurn();
					m_multiBeating = false;
				}*/
			}
		}

		if(!m_multiBeating)
		{
			m_selected->setSelected(false);
			m_selected = nullptr;
		}
	}
}

bool CGame::isMovePossible(sf::Vector2f pos, CPiece* piece)
{
	for(auto it = m_Pieces.begin(); it != m_Pieces.end(); ++it)
	{
		if((*it)->getPosition() == pos)			//chack if there is any piece
			return false;
	}

	sf::Vector2f tmp = piece->getPosition();

	if(!piece->isKing())
	{
		if((((pos - tmp) == sf::Vector2f(100,-100) || (pos - tmp) == sf::Vector2f(-100,-100)) && piece->getColor() == EPieceColor::WHITE) ||
			(((pos - tmp) == sf::Vector2f(100,100) || (pos - tmp) == sf::Vector2f(-100,100)) && piece->getColor() == EPieceColor::BLACK))
		{
			return true;
		}

		if(abs((pos - tmp).x) == 200)
		{	//if player want to make move over 2 fields we need to check if in between is enemy piece
			for(auto it = m_Pieces.begin(); it != m_Pieces.end(); ++it)
			{
				if((*it)->getPosition() == (tmp + (pos - tmp)/2.f) && (*it)->getColor() != piece->getColor())
					return true;
			}
		}
	}
	else
	{
		if(abs((pos - tmp).x) >= 200 && abs((pos - tmp).x) == abs((pos - tmp).y))
		{
			sf::Vector2f gap((pos - tmp).x/(abs((pos - tmp).x)/100), (pos - tmp).y/(abs((pos - tmp).y)/100));
			sf::Vector2f checkPos = tmp+gap;
			int skipped = 0;

			while(checkPos != pos)
			{
				for(auto it = m_Pieces.begin(); it != m_Pieces.end(); ++it)
				{
					if((*it)->getPosition() == checkPos)
					{
						if((*it)->getColor() != piece->getColor())
						{
							++skipped;
						}
						else
							return false;
					}
				}
				checkPos += gap;
			}
			if(skipped <= 1)
				return true;
			else
				return false;
		}
		else if(abs((pos - tmp).x) == 100 && abs((pos - tmp).x) == abs((pos - tmp).y))
		{
			return true;
		}
	}

	return false;
}

bool CGame::isBeatingPossible(CPiece* piece)
{
	sf::Vector2f pos = piece->getPosition();

	if(!piece->isKing())
	{
		for(auto it = m_Pieces.begin(); it != m_Pieces.end(); ++it)
		{
			if(((*it)->getPosition() == pos + sf::Vector2f(100,100) ||
				(*it)->getPosition() == pos + sf::Vector2f(100,-100) ||
				(*it)->getPosition() == pos + sf::Vector2f(-100,-100) ||
				(*it)->getPosition() == pos + sf::Vector2f(-100,100)) &&
				(*it)->getColor() != piece->getColor())
			{
				bool cont = false;
				for(auto it2 = m_Pieces.begin(); it2 != m_Pieces.end(); ++it2)
				{
					if((pos + (((*it)->getPosition() - pos)*2.f)).x < 0 ||
					   (pos + (((*it)->getPosition() - pos)*2.f)).x > 700 ||
					   (pos + (((*it)->getPosition() - pos)*2.f)).y < 0 ||
					   (pos + (((*it)->getPosition() - pos)*2.f)).y > 700)
					    cont = true;

					if((*it2)->getPosition() == pos + (((*it)->getPosition() - pos)*2.f))
						cont = true;
				}
				if(cont)
					continue;
				else
					return true;
			}
		}
		return false;
	}
	else
	{
		for(auto it = m_Pieces.begin(); it != m_Pieces.end(); ++it)
		{
			if((*it)->getPosition() != piece->getPosition() && (*it)->getColor() != piece->getColor())
			{
				if(abs(((*it)->getPosition() - piece->getPosition()).x) == abs(((*it)->getPosition() - piece->getPosition()).y))
				{
					sf::Vector2f dir(((*it)->getPosition() - piece->getPosition()).x/(abs(((*it)->getPosition() - piece->getPosition()).x)/100),
								((*it)->getPosition() - piece->getPosition()).y/(abs(((*it)->getPosition() - piece->getPosition()).y)/100));
					if(((*it)->getPosition() + dir).x < 0 ||
					   ((*it)->getPosition() + dir).x > 700 ||
					   ((*it)->getPosition() + dir).y < 0 ||
					   ((*it)->getPosition() + dir).y > 700)
						break;
					if(isMovePossible((*it)->getPosition() + dir, piece))
						return true;
				}
			}
		}
		return false;
	}
}

void CGame::setPlayerColor(EPieceColor color)
{
	m_playerColor = color;
}

void CGame::setPvP(bool mode)
{
	m_pvp = mode;
}

void CGame::changeTurn()
{
	if(checkForWin())
	{
		std::cout << "Wygral kolor: ";
		if(m_moveFor == EPieceColor::WHITE)
			std::cout << "bialy" << std::endl;
		else
			std::cout << "czarny" << std::endl;
		return;
	}
	//checkIfNoBeating();

	mem.addSet(m_Pieces);

	if(m_playerColor == EPieceColor::BLACK)
		m_moveFor = EPieceColor::WHITE;
	else
		m_moveFor = EPieceColor::BLACK;

	if(m_pvp)
		m_playerColor = m_moveFor;

	std::cout << "Zmiana ruchu" << std::endl;
}

void CGame::checkForKings()
{
	for(auto it = m_Pieces.begin(); it != m_Pieces.end(); ++it)
	{
		if(((*it)->getPosition().y == 0 && (*it)->getColor() == EPieceColor::WHITE) ||
			((*it)->getPosition().y == 700 && (*it)->getColor() == EPieceColor::BLACK)) // if piece is on edge, change it to king
		{
			(*it)->setKing();
		}
	}
}

bool CGame::checkIfBeating()
{
	for(auto it = m_Pieces.begin(); it != m_Pieces.end(); ++it)
	{
		if((*it)->getColor() == m_moveFor && (*it) != m_selected)
		{
			if(isBeatingPossible(*it))
			{
				/*m_Pieces.erase(it);
				it = m_Pieces.begin();*/
				return true;
			}
		}
	}
}

bool CGame::checkForWin()
{
	for(auto it = m_Pieces.begin(); it != m_Pieces.end(); ++it)
	{
		if((*it)->getColor() != m_moveFor)
			return false;
	}
	return true;
}

void CGame::drawPieces(sf::RenderWindow& window)
{
	for(auto it = m_Pieces.begin(); it != m_Pieces.end(); ++it)
	{
		(*it)->draw(window);
	}
}

void CGame::drawBackground(sf::RenderTarget& window)
{
	window.draw(m_drawableBackground);
}

CGame::CGame(void)
{
	m_selected = nullptr;
	m_multiBeating = false;
	m_moveFor = EPieceColor::WHITE;
	m_playerColor = EPieceColor::WHITE;

	m_backgroud.create(800,800, sf::Color(200, 200, 200));

	for(int x = 0; x < 800; ++x)
	{
		for(int y = 0; y < 800; ++y)
		{
			if(((x%200 < 100 && y%200 < 100) || (x%200 >= 100 && y%200 >= 100)))
				m_backgroud.setPixel(x, y, sf::Color(40, 40, 40));
		}
	}
	//m_backgroud.saveToFile("lol.png");
	m_texture.loadFromImage(m_backgroud);
	m_drawableBackground.setTexture(m_texture);

	for(int i = 0; i < 8; ++i)
	{
		for(int j = 0; j < 8; ++j)
		{
			if((j%2 == 0 && i%2 == 0) || (j%2 == 1 && i%2 == 1))
			{
				if(i < 3)
					m_Pieces.push_back(new CPiece(EPieceColor::BLACK, false, sf::Vector2f(j*100, i*100)));
				else if(i >= 5)
					m_Pieces.push_back(new CPiece(EPieceColor::WHITE, false, sf::Vector2f(j*100, i*100)));
			}
		}
	}

	mem.addSet(m_Pieces);

	/*m_Pieces.push_back(new CPiece(EPieceColor::BLACK, false, sf::Vector2f(100, 300)));
	m_Pieces.push_back(new CPiece(EPieceColor::BLACK, false, sf::Vector2f(300, 100)));
	m_Pieces.push_back(new CPiece(EPieceColor::BLACK, false, sf::Vector2f(600, 200)));
	m_Pieces.push_back(new CPiece(EPieceColor::BLACK, false, sf::Vector2f(500, 500)));
	m_Pieces.push_back(new CPiece(EPieceColor::WHITE, false, sf::Vector2f(0, 200)));
	m_Pieces.push_back(new CPiece(EPieceColor::WHITE, false, sf::Vector2f(200, 200)));*/
}


CGame::~CGame(void)
{
	for(auto it = m_Pieces.begin(); it != m_Pieces.end(); ++it)
	{
		delete(*it);
	}
	m_Pieces.clear();
}
