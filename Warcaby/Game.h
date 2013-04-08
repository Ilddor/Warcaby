#pragma once

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

#include "Piece.h"
#include "Misc.h"
#include "Subject.h"

class CGame:
	public Subject
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

	sf::Vector2f m_lastMoveSrc;
	sf::Vector2f m_lastMoveDst;
	std::string m_lastEvent;
public:
	void mousePressed(sf::Event& event);

	bool isMovePossible(sf::Vector2f pos, CPiece* piece);
	bool isBeatingPossible(CPiece* piece);

	void setPlayerColor(EPieceColor color);
	void setPvP(bool mode);

	const std::vector<CPiece*>& getBoard();
	const sf::Vector2f& getLastMoveSrc();
	const sf::Vector2f& getLastMoveDst();
	const std::string& getLastEvent();
	const EPieceColor& getMoveFor();

	void changeTurn();
	void checkForKings();
	bool checkIfBeating();
	bool checkForWin();
	bool checkForDraw();

	void drawPieces(sf::RenderWindow& window);
	void drawBackground(sf::RenderTarget& window);

	CGame(void);
	~CGame(void);
};

