#include "menu.h"

menu::menu(playerSave * _player)
{
	playerPTR = _player;
	newFrame.frame.create(1920, 1080);
	Cursor.loadButtonFromImage("./sprites/hand.png"); 
	backgroundImg.setSprite("./sprites/menuBackground.png");
	backgroundImg.centre(); 
	backgroundImg.setRelativePosition(1.f / 2, 1.f / 2);

	monoArial.loadFromFile("./fonts/arial_monospaced_mt.ttf");
	name.setString(playerPTR->saveName);
	name.setFont(monoArial);
	name.setCharacterSize(40);
	name.setFillColor(sf::Color::White);
	name.setPosition(800, 125);

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

	back.loadButtonFromImage("./sprites/back.png");
	back.setScale(sf::Vector2f(2.5, 2.5));
	back.centre();
	back.setPosition(960, 650);

	exit.loadButtonFromImage("./sprites/exit.png");
	exit.setScale(sf::Vector2f(2.5, 2.5));
	exit.centre();
	exit.setPosition(960, 750);

	help.loadButtonFromImage("./sprites/redBuy.png");
	help.setScale(sf::Vector2f(2.5, 2.5));
	help.centre();
	help.setPosition(960, 550);

	about.loadButtonFromImage("./sprites/greenBuy.png");
	about.setScale(sf::Vector2f(2.5, 2.5));
	about.centre();
	about.setPosition(960, 450);

}

returnFrame * menu::update(sf::Event event, sf::Vector2f mousePos)
{
	//Wiping and intialization for the new frame
	name.setString(playerPTR->saveName);
	newFrame.frame.clear(sf::Color::Transparent);
	newFrame.value = 1;
	Cursor.setPosition(mousePos); 
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		Cursor.pressed();

		//If user clicks "New Game" user will be sent to the new game menu, code located in newGame.h & newGame.cpp
		if (newGame.getGlobalBounds().contains(Cursor.getPosition())) 
		{
			newGame.pressed(true);
			newFrame.value = 2;
		}
		else
		{
			newGame.released();
		}
		//If user clicks "Load" user will be sent to the load menu, code located in loadSave.h & loadSave.cpp
		if (load.getGlobalBounds().contains(Cursor.getPosition())) 
		{
			load.pressed(true);
			newFrame.value = 3;
		}
		else
		{
			load.released();
		}
		//If user clicks "Back" user will be sent to the game Screen, code located in clickerBrain.h & clickerBrain.cpp
		if (back.getGlobalBounds().contains(Cursor.getPosition())) 
		{
			back.pressed(true);
			newFrame.value = 0;
		}
		else
		{
			back.released();
		}
		//If user clicks "Exit", the application will consequently save their game and close. 
		if (exit.getGlobalBounds().contains(Cursor.getPosition())) 
		{
			exit.pressed(true);
			newFrame.value = 4;
		}
		else
		{
			exit.released();
		}

		if (help.getGlobalBounds().contains(Cursor.getPosition()))
		{
			help.pressed(true);
			newFrame.value = 5;
		}
		else
		{
			help.released();
		}

		if (about.getGlobalBounds().contains(Cursor.getPosition()))
		{
			about.pressed(true);
			newFrame.value = 6;
		}
		else
		{
			about.released();
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

	switch (event.key.code)
	{
	case 60: //Key Code 60 is Tab Button
		newFrame.value = 0; //Next Frame the game screen will become active. 
	}

	//Draws all images to screen
	newFrame.frame.draw(backgroundImg);
	newFrame.frame.draw(backgroundBox);
	newFrame.frame.draw(newGame); 
	newFrame.frame.draw(load);
	newFrame.frame.draw(back);
	newFrame.frame.draw(exit);
	newFrame.frame.draw(help);
	newFrame.frame.draw(about);
	newFrame.frame.draw(name);
	newFrame.frame.draw(Cursor); 
	newFrame.frame.display();
	return &newFrame;

}