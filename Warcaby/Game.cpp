#include "Game.h"

void CGame::mousePressed(sf::Event& event)
{
	if(m_selected == nullptr)
	{
		if(event.mouseButton.button == sf::Mouse::Left && m_moveFor == m_playerColor)
		{
			for(auto it = m_Pieces.begin(); it != m_Pieces.end(); ++it)
			{
				if((*it)->pressedOn(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
				{
					if((*it)->getColor() == m_playerColor)
					{
						m_selected = (*it);
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
					for(auto it = m_Pieces.begin(); it != m_Pieces.end(); ++it)
					{
						if((*it)->getPosition() == (prevpos + (newpos - prevpos)/2.f))
						{
							m_Pieces.erase(it);
							break;
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
	for(auto it = m_Pieces.begin(); it != m_Pieces.end(); ++it)
	{
		if((*it)->getPosition() == pos)			//chack if there is any piece
			return false;
	}

	sf::Vector2f tmp = m_selected->getPosition();

	if((pos - tmp) == sf::Vector2f(100,-100) || (pos - tmp) == sf::Vector2f(-100,-100))
	{
		return true;
	}

	if((pos - tmp) == sf::Vector2f(200,-200) || (pos - tmp) == sf::Vector2f(-200,-200) || (pos - tmp) == sf::Vector2f(200,200) || (pos - tmp) == sf::Vector2f(-200,200))
	{	//if player want to make move over 2 fields we need to check if in between is enemy piece
		for(auto it = m_Pieces.begin(); it != m_Pieces.end(); ++it)
		{
			if((*it)->getPosition() == (tmp + (pos - tmp)/2.f) && (*it)->getColor() != m_playerColor)
				return true;
		}
	}

	return false;
}

bool CGame::isBeatingPossible(std::vector<CPiece>::iterator piece)
{
	sf::Vector2f pos = piece->getPosition();

	if(piece->getColor() == EPieceColor::WHITE)
	{

	}
	else
	{
	}
	return false;
}

void CGame::setPlayerColor(EPieceColor color)
{
	m_playerColor = color;
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
					//m_Pieces.push_back(CPiece(EPieceColor::BLACK, false, sf::Vector2f(i*100, j*100)));
				else if(j >= 5);
					//m_Pieces.push_back(CPiece(EPieceColor::WHITE, false, sf::Vector2f(i*100, j*100)));
			}
		}
	}

	m_Pieces.push_back(new CPiece(EPieceColor::BLACK, false, sf::Vector2f(200, 400)));
	m_Pieces.push_back(new CPiece(EPieceColor::WHITE, false, sf::Vector2f(100, 300)));
	m_Pieces.push_back(new CPiece(EPieceColor::WHITE, false, sf::Vector2f(100, 500)));
}


CGame::~CGame(void)
{
	for(auto it = m_Pieces.begin(); it != m_Pieces.end(); ++it)
	{
		delete(*it);
	}
	m_Pieces.clear();
}
