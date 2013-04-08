#include <iostream>
#include <SFML\Graphics.hpp>

#include "Game.h"
#include "Bot.h"
#include "Set.h"

int main()
{
	sf::RenderWindow Window(sf::VideoMode(800,800,32), "Warcaby");
	
	sf::Event Event;

	CGame GameObject;
	CBot BotObject;

	GameObject.addListener(&BotObject);
	BotObject.addGamePtr(&GameObject);

	GameObject.setPlayerColor(EPieceColor::WHITE);
	BotObject.setColor(EPieceColor::BLACK);

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
	}

	return 0;
}