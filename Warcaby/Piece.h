#pragma once

#include <SFML/Graphics.hpp>

#include "Misc.h"

class CPiece
{
private:
	EPieceColor m_color;
	bool m_king;

	sf::CircleShape m_shape;
	sf::CircleShape m_point;

	sf::Vector2f m_position;

	CPiece(void);
public:
	bool pressedOn(sf::Vector2f mousePoint);

	void draw(sf::RenderWindow& window);

	sf::Vector2f getPosition();
	EPieceColor getColor();
	bool isKing();

	void setPosition(sf::Vector2f position);
	void setSelected(bool selected);
	void setKing();

	CPiece(EPieceColor, bool king, sf::Vector2f position);
	~CPiece(void);
};

