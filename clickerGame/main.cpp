#include <SFML/Graphics.hpp>
#include <clickerBrain.h>
#include <menu.h>
#include <newGame.h>
#include <iostream>
int main()
{
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Clicker Game", sf::Style::Fullscreen);
	window.setMouseCursorVisible(false); 
	window.setFramerateLimit(30);
	window.setVerticalSyncEnabled(true);
	window.requestFocus(); 
	clickerBrain clickerScreen; 
	menu menuScreen; 
	newGame newScreen; 
	returnFrame *currentGameFrame = &returnFrame();
	returnFrame * menu = &returnFrame(); 
	playerSave player;
	int keyCode; 
	std::cout << sf::VideoMode::getDesktopMode().width << ',' << sf::VideoMode::getDesktopMode().height << "\n";
	int loading = 0; 
	while (window.isOpen())
	{
		sf::Sprite gameFrame;
		sf::Sprite menuFrame;
		sf::Event event;
		keyCode = -1; 
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close(); 
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
				{
					if (loading != 1)
					{
						loading = 1;
					}
					else
					{
						loading = 0;
					}
				}
				keyCode = event.key.code;
				std::cout << keyCode << "\n"; 
				
			}
		}
		window.clear();

		sf::Vector2f mousePos = { (float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y };
		mousePos = sf::Vector2f(( mousePos.x * (1920.f / window.getSize().x)), mousePos.y * (1080.f / window.getSize().y));//1920, 1080 comes from default framesize of clickerBrain.cpp, 
		
		switch (loading)
		{
		case 0: //Game
			gameFrame.setColor(sf::Color::White);
			currentGameFrame = clickerScreen.update( &player, mousePos);
			gameFrame.setTexture(currentGameFrame->frame.getTexture());
			loading = currentGameFrame->value;
			gameFrame.scale((window.getSize().x / gameFrame.getLocalBounds().width), (window.getSize().y / gameFrame.getLocalBounds().height));
			window.draw(gameFrame);
			break; 
		case 1: //Menu 
			gameFrame.setColor(sf::Color(223, 232, 241, 125));
			gameFrame.setTexture(currentGameFrame->frame.getTexture());
			menu = menuScreen.update(event, mousePos);
			menuFrame.setTexture(menu->frame.getTexture());
			loading = menu->value; 
			gameFrame.scale((window.getSize().x / gameFrame.getLocalBounds().width), (window.getSize().y / gameFrame.getLocalBounds().height));
			menuFrame.scale((window.getSize().x / menuFrame.getLocalBounds().width), (window.getSize().y / menuFrame.getLocalBounds().height));
			window.draw(gameFrame);
			window.draw(menuFrame);
			break; 
		case 2: //new Game
			gameFrame.setColor(sf::Color(223, 232, 241, 125));
			gameFrame.setTexture(currentGameFrame->frame.getTexture());
			menu = newScreen.update(keyCode, mousePos);
			menuFrame.setTexture(menu->frame.getTexture());
			

			gameFrame.scale((window.getSize().x / gameFrame.getLocalBounds().width), (window.getSize().y / gameFrame.getLocalBounds().height));
			menuFrame.scale((window.getSize().x / menuFrame.getLocalBounds().width), (window.getSize().y / menuFrame.getLocalBounds().height));
			window.draw(gameFrame);
			window.draw(menuFrame);
			break; 
		case 3: //loading

			break;
		default: break;
		}


		
		window.display();
	}

	return 0;
}