#include <SFML/Graphics.hpp>
#include <clickerBrain.h>
#include <iostream>
int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Clicker Game", sf::Style::Fullscreen);
	window.setMouseCursorVisible(false); 
	clickerBrain clickerScreen; 
	while (window.isOpen())
	{
		sf::Event event;
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
			}
		}
		window.clear();
		window.draw(sf::Sprite (clickerScreen.update(event)->frame.getTexture()));
		window.display();
	}

	return 0;
}