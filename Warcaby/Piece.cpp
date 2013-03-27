#include "Piece.h"

bool CPiece::pressedOn(sf::Vector2f mousePoint)
{
	if(mousePoint.x > m_shape.getPosition().x && mousePoint.x < m_shape.getPosition().x+100 && mousePoint.y > m_shape.getPosition().y && mousePoint.y < m_shape.getPosition().y+100)
		return true;
	else
		return false;
}

void CPiece::draw(sf::RenderWindow& window)
{
	//window.draw(m_sprite);
	window.draw(m_shape);
}

sf::Vector2f CPiece::getPosition()
{
	return m_shape.getPosition();
}

void CPiece::setPosition(sf::Vector2f position)
{
	m_shape.setPosition(position);
}

void CPiece::setSelected(bool selected)
{
	if(selected)
	{
		if(m_color == EPieceColor::WHITE)
			m_shape.setFillColor(sf::Color(200,200,255));
		else
			m_shape.setFillColor(sf::Color(0, 0, 55));
	}
	else
	{
		if(m_color == EPieceColor::WHITE)
			m_shape.setFillColor(sf::Color::White);
		else
			m_shape.setFillColor(sf::Color::Black);
	}
}

CPiece::CPiece(EPieceColor color, bool king, sf::Vector2f position)
{
	m_color = color;
	m_king = king;

	//m_shape.setRadius(50.f);

	m_shape = *(new sf::CircleShape(50.f));
	if(m_color == EPieceColor::WHITE)
		m_shape.setFillColor(sf::Color::White);
	else
		m_shape.setFillColor(sf::Color::Black);
	m_shape.setPosition(position);
}

CPiece::CPiece(void)
{
}


CPiece::~CPiece(void)
{
}
