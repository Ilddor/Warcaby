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

	std::vector<CPiece*> m_Pieces;

	EPieceColor m_moveFor;
	EPieceColor m_playerColor;
	
	CPiece* m_selected;
public:
	void mousePressed(sf::Event& event);

	bool isMovePossible(sf::Vector2f pos);
	bool isBeatingPossible(std::vector<CPiece>::iterator piece);

	void setPlayerColor(EPieceColor color);

	void drawPieces(sf::RenderWindow& window);
	void drawBackground(sf::RenderTarget& window);

	CGame(void);
	~CGame(void);
};

