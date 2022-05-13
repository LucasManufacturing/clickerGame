#include "clickerBrain.h"
std::string clickerBrain::to_dollar(float input)
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

clickerBrain::clickerBrain()
{
	newFrame.frame.create(1920, 1080); 
	newFrame.value = 0; 

	trial = arial.loadFromFile("./fonts/arial.ttf");
	
	
	moneyText.setFont(arial);
	moneyText.setCharacterSize(60); 
	moneyText.setFillColor(sf::Color::White);
	moneyText.setPosition(860, 0); 

	clickText.setFont(arial);
	clickText.setCharacterSize(60);
	clickText.setFillColor(sf::Color::White);
	clickText.setPosition(430, 0);

	passiveText.setFont(arial);
	passiveText.setCharacterSize(60);
	passiveText.setFillColor(sf::Color::White);
	passiveText.setPosition(1290, 0);

	cog.loadButtonFromImage("./sprites/cog.png");
	cog.setOrigin(sf::Vector2f(128, 0)); 
	cog.setPosition(1920, 0); 

	save.loadButtonFromImage("./sprites/saveIcon.png");
	save.setPosition(0, 0); 


	backGround.setSprite("./sprites/backGround.png");
	backGround.centre(); 
	backGround.setRelativePosition(1.f / 2, 1.f / 2); 

	clickButton.setScale(3.f, 3.f);
	clickButton.loadButtonFromImage("./sprites/greenClick.png");
	clickButton.centre(); 
	clickButton.setRelativePosition(1.f/2, 1.f/8); 
//Modifiers

}

void clickerBrain::click()
{
	
}

returnFrame * clickerBrain::update(playerSave * _player, sf::Vector2f mousePos)
{
	//Wiping and intialization for the new frame
	newFrame.frame.clear(sf::Color::White); 
	newFrame.frame.draw(backGround); 
	newFrame.value = 0;
	frameCount.add(); 
	newFrame.frame.draw(clickButton);
	//Cursor.updatePos();
	Cursor.setPosition(mousePos);
	moneyText.setString(to_dollar(_player->money)); 
	clickText.setString(to_dollar(_player->clickValue)); 
	passiveText.setString(to_dollar(_player->passiveValue));
	_player->money = _player->money + (_player->passiveValue/framesPerTic);

	//Cursor and Mouse
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		Cursor.pressed();
		if (clickButton.getGlobalBounds().contains(Cursor.getPosition()))
		{
			if (clickButton.pressed(true))
			{
				_player->money += _player->clickValue;
			}
		}
		else
		{
			clickButton.released();
		}

		if (cog.getGlobalBounds().contains(Cursor.getPosition()))
		{
			cog.pressed(); 
			newFrame.value = 1;
		}
		else {
			cog.released(); 
		}
		if (save.getGlobalBounds().contains(Cursor.getPosition()))
		{
			save.pressed(); 
			_player->saveGame(); 
		}
		else
		{
			save.released(); 
		}
		for (auto i = _player->modifierList.begin(); i != _player->modifierList.end(); i++)
		{
			if ((*i)->buy.getGlobalBounds().contains(Cursor.getPosition()))
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

	for (auto i = _player->modifierList.begin(); i != _player->modifierList.end(); i++)
	{
		
		(*i)->costText.setString(to_dollar((*i)->getCost())); 
		newFrame.frame.draw((*i)->buy); 
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

