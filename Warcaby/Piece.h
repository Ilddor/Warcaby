#pragma once

#include <SFML/Graphics.hpp>
class CPiece
{
private:
	bool m_color;
	bool m_king;

	sf::CircleShape m_shape;

	sf::Vector2f m_position;

	CPiece(void);
public:
	bool pressedOn(sf::Vector2f mousePoint);

	void draw(sf::RenderWindow& window);

	void setPosition(sf::Vector2f position);

	CPiece(bool color, bool king, sf::Vector2f position);
	~CPiece(void);
};

