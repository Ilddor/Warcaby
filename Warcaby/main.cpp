#include <iostream>
#include <time.h>
#include <SFML\Graphics.hpp>

#include "Game.h"
#include "Bot.h"
#include "Set.h"
#include "PlayerTypeSecond.h"

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
	//CBot BotObject;

	//GameObject.addListener(&BotObject);
	//BotObject.addGamePtr(&GameObject);
	CPlayerTypeSecond BotObject;
	GameObject.addListener(&BotObject);
	BotObject.addGamePtr(&GameObject);
	srand(time(NULL));
	if(rand()%2 == 0)
	{
		GameObject.setPlayerColor(EPieceColor::BLACK);
		BotObject.setColor(EPieceColor::WHITE);
	}
	else
	{
		GameObject.setPlayerColor(EPieceColor::WHITE);
		BotObject.setColor(EPieceColor::BLACK);
	}


	GameObject.setPvP(false);
	GameObject.start();

	while(Window.isOpen())
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

	return 0;
}