#pragma once
class CMove
{
private:
	char m_source, m_destination, m_info; //for position info first half of byte describe x position on board second y
									//for info 1bit describe if that was move of winning player
									//2 bit describe what color it was (1 = white)
	CMove(void);
public:
	void setWinning();

	bool getColor();	//true for white, false for black

	CMove(char src, char dst, char info);
	CMove(int srcx, int srcy, int dstx, int dsty, bool winning, bool color);
	~CMove(void);
};

