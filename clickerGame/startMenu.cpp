#include "startMenu.h"

startMenu::startMenu()
{
	newFrame.frame.create(1920, 1080);
	Cursor.loadButtonFromImage("./sprites/hand.png");
	backgroundImg.setSprite("./sprites/menuBackground.png");
	backgroundImg.centre();
	backgroundImg.setRelativePosition(1.f / 2, 1.f / 2);

	backgroundBox.setSprite("./sprites/menuBackgroundBox.png");
	backgroundBox.centre();
	backgroundBox.setRelativePosition(1.f / 2, 1.f / 2);

	newGame.loadButtonFromImage("./sprites/newGame.png");
	newGame.setScale(sf::Vector2f(2.5, 2.5));
	newGame.centre();
	newGame.setPosition(960, 250);

	load.loadButtonFromImage("./sprites/load.png");
	load.setScale(sf::Vector2f(2.5, 2.5));
	load.centre();
	load.setPosition(960, 350);
}

returnFrame * startMenu::update(sf::Event event, sf::Vector2f mousePos)
{
	//Wiping and intialization for the new frame
	newFrame.frame.clear(sf::Color::Transparent);
	newFrame.value = -1;
	Cursor.setPosition(mousePos);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		Cursor.pressed();
		if (newGame.getGlobalBounds().contains(Cursor.getPosition()))
		{
			newGame.pressed(true);
			newFrame.value = 2;
		}
		else
		{
			newGame.released();
		}
		if (load.getGlobalBounds().contains(Cursor.getPosition()))
		{
			load.pressed(true);
			newFrame.value = 3;
		}
		else
		{
			load.released();
		}
	}
	else
	{
		for (auto i = buttonList.begin(); i != buttonList.end(); i++)
		{
			(*i)->released();
		}
		Cursor.released();
	}


	//
	newFrame.frame.draw(backgroundImg);
	newFrame.frame.draw(backgroundBox);
	newFrame.frame.draw(newGame);
	newFrame.frame.draw(load);
	newFrame.frame.draw(Cursor);
	newFrame.frame.display();
	return &newFrame;

}