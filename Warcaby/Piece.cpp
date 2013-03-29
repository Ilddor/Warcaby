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
	if(m_king)
		window.draw(m_point);
}

sf::Vector2f CPiece::getPosition()
{
	return m_shape.getPosition();
}

EPieceColor CPiece::getColor()
{
	return m_color;
}

bool CPiece::isKing()
{
	return m_king;
}

void CPiece::setPosition(sf::Vector2f position)
{
	m_shape.setPosition(position);
	m_point.setPosition(position + sf::Vector2f(40,40));
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

void CPiece::setKing()
{
	m_king = true;
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

	m_point.setRadius(10.f);
	m_point.setFillColor(sf::Color::Red);
	m_point.setPosition(position + sf::Vector2f(40,40));
}

CPiece::CPiece(void)
{
}


CPiece::~CPiece(void)
{
}
