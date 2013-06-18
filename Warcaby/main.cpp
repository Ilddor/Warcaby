#include <iostream>
#include <time.h>
#include <SFML\Graphics.hpp>

#include "Game.h"
#include "Bot.h"
#include "Set.h"
#include "PlayerTypeSecond.h"
#include <fstream>

int main()
{
	sf::RenderWindow Window(sf::VideoMode(800,800,32), "Warcaby");
	
	sf::Event Event;

	CGame GameObject;

	GameObject.setWindow(&Window);

	///// 2BOT v each other version
	//CBot BotObject;

	//GameObject.addListener(&BotObject);
	//BotObject.addGamePtr(&GameObject);
	//CBot BotObject2;

	//GameObject.addListener(&BotObject2);
	//BotObject2.addGamePtr(&GameObject);

	/*GameObject.setSelfgame(true);
	GameObject.setPlayerColor(EPieceColor::BLACK);
	BotObject.setColor(EPieceColor::BLACK);
	BotObject2.setColor(EPieceColor::WHITE);*/
	///// 1BOT v player VERSION
	CBot BotObject;

	GameObject.addListener(&BotObject);
	BotObject.addGamePtr(&GameObject);
	CPlayerTypeSecond BotObject1;
	GameObject.addListener(&BotObject1);
	BotObject1.addGamePtr(&GameObject);
	srand(time(NULL));
	if(rand()%2 == 0)
	{
		BotObject1.setColor(EPieceColor::BLACK);
		BotObject.setColor(EPieceColor::WHITE);
	}
	else
	{
		BotObject1.setColor(EPieceColor::WHITE);
		BotObject.setColor(EPieceColor::BLACK);
	}

	GameObject.setPvP(false);
	GameObject.start();

	while(Window.isOpen() && GameObject.m_gamesPlayed < 7)
	{
		while(Window.pollEvent(Event))
		{
			switch(Event.type)
			{
			case sf::Event::Closed :
				Window.close();
			case sf::Event::MouseButtonPressed :
				GameObject.mousePressed(Event);
			}
		}

		Window.clear();

		GameObject.drawBackground(Window);

		GameObject.drawPieces(Window);

		Window.display();

		GameObject.restart();
	}
	std::fstream outcome;
	outcome.open("outcome.txt",std::ios::app);
	outcome << "Games played\t" << GameObject.m_gamesPlayed << "\twinprecentage:\t" << GameObject.m_gamesWonByBot/GameObject.m_gamesPlayed*100 << std::endl;
	outcome.close();
	return 0;
}