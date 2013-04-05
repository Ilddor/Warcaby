#include "Bot.h"
#include <string>
#include <iostream>
#include "Misc.h"

void CBot::update(std::string eventName, EPieceColor color)
{
	if(eventName == "turn" && m_color == color)
	{
		  std::cout << "I think I should make a move now" << std::endl;
		  //Here we proceed with magic such as getting board, thinking of best move and killing the other motherfucker
	}
	else if(eventName == "gameEnd")
	{
		  if(m_color == color)
		  {
		  	  std::cout << "Yippie!" << std::endl;
			  //Here we will boast about how we just killed that motherfucker
		  }
		  else
		  {
		  	  std::cout << "Well shit :(" << std::endl;
			  //Here we will cry like a little girl and get suicidal thoughts ;-)
		  }
	}
}


CBot::CBot(void)
{
	 
}


CBot::~CBot(void)
{
}
