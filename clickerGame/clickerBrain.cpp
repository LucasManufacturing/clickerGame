#include "clickerBrain.h"

std::string to_dollar(float input)
{
	std::string str;
	str = std::to_string(input);
	if (input < 1000)
	{
		str.erase(str.begin() + str.find('.') + 3, str.end());
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

	cog.setSprite("./sprites/cog.png");
	cog.setOrigin(sf::Vector2f(128, 0)); 
	cog.setPosition(1920, 0); 

	backGround.setSprite("./sprites/backGround.png");
	backGround.centre(); 
	backGround.setRelativePosition(1.f / 2, 1.f / 2); 

	clickButton.setScale(3.f, 3.f);
	clickButton.loadButtonFromImage("./sprites/greenClick.png");
	clickButton.centre(); 
	clickButton.setRelativePosition(1.f/2, 1.f/8); 
//Modifiers
{

		pencil = modifier("./sprites/pencil.png");
		pencil.setPosition(sf::Vector2f(416, 348));
		pencil.setCost(25.f);
		pencil.setClickModifier(1.f);

		scissors = modifier("./sprites/scissors.png");
		scissors.setPosition(sf::Vector2f(416, 540));
		scissors.setCost(50.f);
		scissors.setClickModifier(5.f);

		coffee = modifier("./sprites/coffee.png");
		coffee.setPosition(sf::Vector2f(416, 732));
		coffee.setCost(100.f);
		coffee.setClickModifier(15.f);

		thief = modifier("./sprites/thief.png");
		thief.setPosition(sf::Vector2f(1376, 348));
		thief.setCost(75.f);
		thief.setPassiveModifier(1.f);

		stock = modifier("./sprites/stocks.png");
		stock.setPosition(sf::Vector2f(1376, 540));
		stock.setCost(150.f);
		stock.setPassiveModifier(5.f);

		manager = modifier("./sprites/manager.png");
		manager.setPosition(sf::Vector2f(1376, 732));
		manager.setCost(300.f);
		manager.setPassiveModifier(10.f);

		for (auto i = modifierList.begin(); i != modifierList.end(); i++)
		{
			(*i)->icon.setScale(1.5, 1.5); 
			(*i)->buy.setScale(2.0, 2.0);
			(*i)->costText.setFont(arial);
			(*i)->costText.setCharacterSize(30);
			(*i)->costText.setFillColor(sf::Color::White);
		}
	}
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
			newFrame.value = 1;
		}

		for (auto i = modifierList.begin(); i != modifierList.end(); i++)
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
		for (auto i = modifierList.begin(); i != modifierList.end(); i++)
		{
			(*i)->buy.released();
		}
		Cursor.released();
		clickButton.released();
	}

	for (auto i = modifierList.begin(); i != modifierList.end(); i++)
	{
		
		(*i)->costText.setString(to_dollar((*i)->getCost())); 
		newFrame.frame.draw((*i)->buy); 
		newFrame.frame.draw((*i)->icon);
		newFrame.frame.draw((*i)->costText);
	}
	newFrame.frame.draw(moneyText); 
	newFrame.frame.draw(cog); 
	newFrame.frame.draw(Cursor); 
	newFrame.frame.display();
	return &newFrame; 
	
}

