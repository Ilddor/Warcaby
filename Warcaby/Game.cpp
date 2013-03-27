#include "Game.h"

void CGame::mousePressed(sf::Event& event)
{
	if(m_selected == nullptr)
	{
		if(event.mouseButton.button == sf::Mouse::Left && m_moveFor == m_playerColor)
		{
			if(m_playerColor == EPieceColor::WHITE)
			{
				for(auto it = m_whitePieces.begin(); it != m_whitePieces.end(); ++it)
				{
					if(it->pressedOn(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
					{
						m_selected = it._Ptr;
						m_selected->setSelected(true);
					}
				}
			}
			else
			{
				for(auto it = m_blackPieces.begin(); it != m_blackPieces.end(); ++it)
				{
					if(it->pressedOn(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
					{
						m_selected = it._Ptr;
						m_selected->setSelected(true);
					}
				}
			}
		}
	}
	else
	{
		if(m_backgroud.getPixel(event.mouseButton.x, event.mouseButton.y) == sf::Color(40, 40, 40))
		{
			if(isMovePossible(sf::Vector2f(event.mouseButton.x-event.mouseButton.x%100, event.mouseButton.y-event.mouseButton.y%100)))	//check if requested move is possible
			{
				sf::Vector2f newpos(event.mouseButton.x-event.mouseButton.x%100, event.mouseButton.y-event.mouseButton.y%100);
				sf::Vector2f prevpos(m_selected->getPosition());
				if(abs(newpos.x - m_selected->getPosition().x) == 200)	//if the move was over 2 fields -> delete skipped piece
				{
					if(m_playerColor == EPieceColor::WHITE)
					{
						for(auto it = m_blackPieces.begin(); it != m_blackPieces.end(); ++it)
						{
							if(it->getPosition() == (prevpos + (newpos - prevpos)/2.f))
							{
								m_blackPieces.erase(it);
								break;
							}
						}
					}
					else
					{
						for(auto it = m_whitePieces.begin(); it != m_whitePieces.end(); ++it)
						{
							if(it->getPosition() == (prevpos + (newpos - prevpos)/2.f))
							{
								m_whitePieces.erase(it);
								break;
							}
						}
					}
				}
				else
				{
					if(m_playerColor == EPieceColor::BLACK)
						m_moveFor = EPieceColor::WHITE;
					else
						m_moveFor = EPieceColor::BLACK;
				}

				m_selected->setPosition(newpos);
			}
		}

		m_selected->setSelected(false);
		m_selected = nullptr;
	}
}

bool CGame::isMovePossible(sf::Vector2f pos)
{
	for(auto it = m_whitePieces.begin(); it != m_whitePieces.end(); ++it)
	{
		if(it->getPosition() == pos)			//chack if there is any white piece
			return false;
	}
	for(auto it = m_blackPieces.begin(); it != m_blackPieces.end(); ++it)
	{
		if(it->getPosition() == pos)			//the same for black pieces
			return false;
	}

	sf::Vector2f tmp = m_selected->getPosition();

	if(m_playerColor == EPieceColor::WHITE)
	{
		if((pos - tmp) == sf::Vector2f(100,-100) || (pos - tmp) == sf::Vector2f(-100,-100))
		{
			return true;
		}

		if((pos - tmp) == sf::Vector2f(200,-200) || (pos - tmp) == sf::Vector2f(-200,-200) || (pos - tmp) == sf::Vector2f(200,200) || (pos - tmp) == sf::Vector2f(-200,200))
		{	//if player want to make move over 2 fields we need to check if in between is enemy piece
			bool between = false;
			for(auto it = m_blackPieces.begin(); it != m_blackPieces.end(); ++it)
			{
				if(it->getPosition() == (tmp + (pos - tmp)/2.f))
					between = true;
			}
			if(between)
				return true;
		}
	}
	else
	{
		if((pos - tmp) == sf::Vector2f(100,100) || (pos - tmp) == sf::Vector2f(-100,100))
		{
			return true;
		}

		if((pos - tmp) == sf::Vector2f(200,200) || (pos - tmp) == sf::Vector2f(-200,200) || (pos - tmp) == sf::Vector2f(200,-200) || (pos - tmp) == sf::Vector2f(-200,-200))
		{	//if player want to make move over 2 fields we need to check if in between is enemy piece
			bool between = false;
			for(auto it = m_whitePieces.begin(); it != m_whitePieces.end(); ++it)
			{
				if(it->getPosition() == (tmp + (pos - tmp)/2.f))
					between = true;
			}
			if(between)
				return true;
		}
	}

	return false;
}

bool CGame::isBeatingPossible(std::vector<CPiece>::iterator piece)
{
	return false;
}

void CGame::setPlayerColor(EPieceColor color)
{
	m_playerColor = color;
}

void CGame::drawPieces(sf::RenderWindow& window)
{
	for(auto it = m_blackPieces.begin(); it != m_blackPieces.end(); ++it)
	{
		it->draw(window);
	}
	for(auto it = m_whitePieces.begin(); it != m_whitePieces.end(); ++it)
	{
		it->draw(window);
	}
}

void CGame::drawBackground(sf::RenderTarget& window)
{
	window.draw(m_drawableBackground);
}

CGame::CGame(void)
{
	m_selected = nullptr;
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
			if((i%2 == 0 && j%2 == 0) || (i%2 == 1 && j%2 == 1))
			{
				if(j < 3);
					//m_blackPieces.push_back(CPiece(EPieceColor::BLACK, false, sf::Vector2f(i*100, j*100)));
				else if(j >= 5);
					//m_whitePieces.push_back(CPiece(EPieceColor::WHITE, false, sf::Vector2f(i*100, j*100)));
			}
		}
	}

	m_blackPieces.push_back(CPiece(EPieceColor::BLACK, false, sf::Vector2f(200, 400)));
	m_whitePieces.push_back(CPiece(EPieceColor::WHITE, false, sf::Vector2f(100, 300)));
}


CGame::~CGame(void)
{
	m_blackPieces.clear();
	m_whitePieces.clear();
}
