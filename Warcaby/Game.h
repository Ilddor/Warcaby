#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Piece.h"
#include "Misc.h"

class CGame
{
private:
	sf::Image m_backgroud;
	sf::Sprite m_drawableBackground;
	sf::Texture m_texture;

	std::vector<CPiece> m_whitePieces;
	std::vector<CPiece> m_blackPieces;

	EPieceColor m_moveFor;
	
	CPiece* m_selected;
public:
	void mousePressed(sf::Event& event);

	void drawPieces(sf::RenderWindow& window);
	void drawBackground(sf::RenderTarget& window);

	CGame(void);
	~CGame(void);
};

