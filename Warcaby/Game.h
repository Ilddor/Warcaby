#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

#include "Piece.h"
#include "Misc.h"
#include "BotMemory.h"

class CGame
{
private:
	sf::Image m_backgroud;
	sf::Sprite m_drawableBackground;
	sf::Texture m_texture;

	std::vector<CPiece*> m_Pieces;

	EPieceColor m_moveFor;
	EPieceColor m_playerColor;
	bool m_pvp;
	
	CPiece* m_selected;
	bool m_multiBeating;

	CBotMemory mem, data;
public:
	void mousePressed(sf::Event& event);

	bool isMovePossible(sf::Vector2f pos, CPiece* piece);
	bool isBeatingPossible(CPiece* piece);

	void setPlayerColor(EPieceColor color);
	void setPvP(bool mode);

	void changeTurn();
	void checkForKings();
	bool checkIfBeating();
	bool checkForWin();

	void drawPieces(sf::RenderWindow& window);
	void drawBackground(sf::RenderTarget& window);

	CGame(void);
	~CGame(void);
};

