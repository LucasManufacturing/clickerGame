#include "clickerBrain.h"



clickerBrain::clickerBrain()
{
	newFrame.frame.create(1920, 1080); 
	newFrame.value = 0; 
	clickButton.setScale(3.f, 3.f);
}

returnFrame * clickerBrain::update(sf::Event event)
{
	//Wiping and intialization for the new frame
	newFrame.frame.clear(sf::Color::White); 
	newFrame.value = 0;
	frameCount.add(); 
	newFrame.frame.draw(clickButton);
	Cursor.updatePos();


	//Cursor and Mouse
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		Cursor.pressed();
		if (clickButton.getGlobalBounds().contains(Cursor.getPosition()))
		{
			clickButton.pressed();
		}
		else
		{
			clickButton.released();
		}
	}
	else
	{
		Cursor.released();
		clickButton.released();
	}
	
	newFrame.frame.draw(Cursor); 
	newFrame.frame.display();
	return &newFrame; 
	
}