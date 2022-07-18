#include "clickerBrain.h"


clickerBrain::clickerBrain()
{
	//intializes the frame to draw onto. 
	newFrame.frame.create(1920, 1080); 
	//sets a default value.
	newFrame.value = 0; 

	//loads the font from a file
	arial.loadFromFile("./fonts/arial.ttf");
	
	//Configures graphical settings of moneyText
	moneyText.setFont(arial);
	moneyText.setOutlineColor(sf::Color::Black);
	moneyText.setOutlineThickness(3);
	moneyText.setCharacterSize(60); 
	moneyText.setFillColor(sf::Color::White);
	moneyText.setPosition(885, 0); 

	//Configures graphical settings of clickText
	clickText.setFont(arial);
	clickText.setOutlineColor(sf::Color::Black);
	clickText.setOutlineThickness(3);
	clickText.setCharacterSize(60);
	clickText.setFillColor(sf::Color::White);
	clickText.setPosition(430, 0);

	//Configures graphical settings of passiveText
	passiveText.setFont(arial);
	passiveText.setOutlineColor(sf::Color::Black);
	passiveText.setOutlineThickness(3);
	passiveText.setCharacterSize(60);
	passiveText.setFillColor(sf::Color::White);
	passiveText.setPosition(1290, 0);

	//Configures graphical settings of cog
	cog.loadButtonFromImage("./sprites/cog.png");
	cog.setOrigin(sf::Vector2f(128, 0)); 
	cog.setPosition(1920, 0); 

	//Configures graphical settings of save
	save.loadButtonFromImage("./sprites/saveIcon.png");
	save.setPosition(0, 0); 

	//Configures graphical settings of backGround
	backGround.setSprite("./sprites/backGround.png");
	backGround.centre(); 
	backGround.setRelativePosition(1.f / 2, 1.f / 2); 

	//Configures graphical settings of clickButton
	clickButton.setScale(3.f, 3.f);
	clickButton.loadButtonFromImage("./sprites/greenClick.png");
	clickButton.centre(); 
	clickButton.setRelativePosition(1.f/2, 1.f/8); 

}

returnFrame * clickerBrain::update(playerSave * _player, sf::Vector2f mousePos)
{
	//Wiping and intialization for the new frame
	newFrame.frame.clear(sf::Color::White); 
	newFrame.frame.draw(backGround); 
	newFrame.value = 0;
	newFrame.frame.draw(clickButton);

	//Updates constantly changing objects.
	Cursor.setPosition(mousePos); //updates position of cursor
	moneyText.setString(to_dollar(_player->money)); //updates moneyText to new money value
	clickText.setString(to_dollar(_player->clickValue) + "/click"); //updates clickText to new click value
	passiveText.setString(to_dollar(_player->passiveValue) + "/sec");//updates passiveText to new passive value
	_player->money = _player->money + (_player->passiveValue/framesPerTic);

	//Cursor and Mouse
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) //detects whether user pressed left click
	{
		Cursor.pressed();
		//These below contain all button logic
		if (clickButton.getGlobalBounds().contains(Cursor.getPosition())) //detects if cursor is within the button's bounds
		{
			if (clickButton.pressed(true)) //Passes true to make function return whether the button was clicked before. This is to not allow automatic collection of money by holding left click
			{
				_player->money += _player->clickValue; //money is added to user
			}
		}
		else
		{
			clickButton.released(); //if cursor wasn't within bounds button appears unpressed. 
		}
		if (cog.getGlobalBounds().contains(Cursor.getPosition())) //detects if cursor is within the button's bounds
		{
			cog.pressed(); //button appears pressed
			newFrame.value = 1; //switches active screen to menu
		}
		else {
			cog.released(); //releases button
		}
		if (save.getGlobalBounds().contains(Cursor.getPosition())) //detects if cursor is within the button's bounds
		{
			save.pressed(); //button appears pressed
			_player->saveGame(); //game becomes saved
		}
		else
		{
			save.released(); //releases button
		}
		for (auto i = _player->modifierList.begin(); i != _player->modifierList.end(); i++) //loop through all modifiers 
		{
			if ((*i)->buy.getGlobalBounds().contains(Cursor.getPosition())) //detects if cursor is within the button's bounds
			{
				if ((*i)->buy.pressed(true))//if button wasn't pressed last frame execute tryBuy
				{
					(*i)->tryBuy(&_player->money, &_player->clickValue, &_player->passiveValue);
				}

			}
			else
			{
				(*i)->buy.released();
			}
		}
	}
	else
	{
		for (auto i = _player->modifierList.begin(); i != _player->modifierList.end(); i++)
		{
			(*i)->buy.released();
		}
		save.released(); 
		cog.released(); 
		Cursor.released();
		clickButton.released();
	}
	//End of Button Logic

	//Handles drawing of buttons
	for (auto i = _player->modifierList.begin(); i != _player->modifierList.end(); i++)
	{
		//Updates button cost and color each frame. 
		(*i)->costText.setString(to_dollar((*i)->getCost())); 
		if ((*i)->getCost() <= _player->money) //if player can afford colour is green
		{
			newFrame.frame.draw((*i)->buy);
			(*i)->costText.setFillColor(sf::Color::Green);
		}
		else //if player cant afford colour is red
		{
			newFrame.frame.draw((*i)->redBuy);
			(*i)->costText.setFillColor(sf::Color::Red);
		}
		
		newFrame.frame.draw((*i)->modifierText); 
		newFrame.frame.draw((*i)->icon);
		newFrame.frame.draw((*i)->costText);
	}
	newFrame.frame.draw(clickText);
	newFrame.frame.draw(passiveText);
	newFrame.frame.draw(moneyText); 
	newFrame.frame.draw(cog); 
	newFrame.frame.draw(save);
	newFrame.frame.draw(Cursor); 
	newFrame.frame.display();
	return &newFrame; 
	
}

std::string clickerBrain::to_dollar(float input) //converts float values to a string format of xxx.xx unit
{
	std::string str;
	str = std::to_string(input);
	if (input < 1000)
	{
		str.erase(str.begin() + str.find('.') + 3, str.end());
	}
	else if (input >= 18446744073709551615)//largest int possible 
	{
		str = ("18.44Q+");
	}
	else if (input >= 1000000000000000000)
	{
		str = std::to_string((input + 0.5) / 1000000000000000000);
		str.erase(str.begin() + str.find('.') + 3, str.end());
		str.append("Q");
	}
	else if (input >= 1000000000000000)
	{
		str = std::to_string((input + 0.5) / 1000000000000000);
		str.erase(str.begin() + str.find('.') + 3, str.end());
		str.append("q");
	}
	else if (input >= 1000000000000)
	{
		str = std::to_string((input + 0.5) / 1000000000000);
		str.erase(str.begin() + str.find('.') + 3, str.end());
		str.append("T");
	}
	else if (input >= 1000000000)
	{

		str = std::to_string((input + 0.5) / 1000000000);
		str.erase(str.begin() + str.find('.') + 3, str.end());
		str.append("B");
	}
	else if (input >= 1000000)
	{

		str = std::to_string((input + 0.5) / 1000000);
		str.erase(str.begin() + str.find('.') + 3, str.end());
		str.append("M");
	}
	else if (input >= 1000)
	{

		str = std::to_string((input + 0.5) / 1000);
		str.erase(str.begin() + str.find('.') + 3, str.end());
		str.append("K");
	}


	return str;
}