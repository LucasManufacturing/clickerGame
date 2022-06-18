#include "infoScreen.h"
infoScreen::infoScreen(std::string _path, int _int)
{
	screenValue = _int; 
	newFrame.frame.create(1920, 1080);
	text.setSprite(_path);
	text.centre();
	text.setPosition(960, 540); 

	back.loadButtonFromImage("./sprites/back.png");
	back.centre();
	back.setPosition(960, 1000);
	back.setScale(3.f, 3.f); 
	Cursor.loadButtonFromImage("./sprites/hand.png"); 
}
returnFrame* infoScreen::update(sf::Vector2f _mousePos)
{
	newFrame.frame.clear(sf::Color::Transparent); 
	newFrame.value = screenValue; 

	Cursor.setPosition(_mousePos); 
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		Cursor.pressed(); 
		if (back.getGlobalBounds().contains(_mousePos))
		{
			back.pressed(); 
			newFrame.value = 1;
		}
		else
		{
			back.released(); 
		}
	}
	else
	{
		Cursor.released(); 
		back.released(); 
	}
	newFrame.frame.draw(text);
	newFrame.frame.draw(back);
	newFrame.frame.draw(Cursor); 
	newFrame.frame.display(); 
	return &newFrame; 
}