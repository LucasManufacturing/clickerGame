#include "clickerBrain.h"


clickerBrain::clickerBrain()
{
	newFrame.frame.create(1920, 1080); 
	newFrame.value = 0; 

	arial.loadFromFile("./fonts/arial.ttf");

	moneyText.setFont(arial);
	moneyText.setCharacterSize(30); 
	moneyText.setFillColor(sf::Color::Black);
	moneyText.setPosition(1.f/2, 2.f/9); 

	managerCost.setFont(arial);
	managerCost.setCharacterSize(30);
	managerCost.setFillColor(sf::Color::Black);
	managerCost.setPosition(480, 400);

	stockCost.setFont(arial);
	stockCost.setCharacterSize(30);
	stockCost.setFillColor(sf::Color::Black);
	stockCost.setPosition(1440, 400);

	clickButton.setScale(3.f, 3.f);
	clickButton.loadButtonFromImage("./sprites/greenClick.png");
	clickButton.setRelativePosition(1.f/2, 1.f/8); 

	manager = modifier("./sprites/manager.png");
	manager.icon.setRelativePosition(1.f / 4.f, 4.f / 9.f);
	manager.buy.setRelativePosition(4.8 / 16, 4.1 / 9);
	manager.setCost(25.f);
	manager.setClickModifier(1.f);

	stock = modifier("./sprites/stocks.png");
	stock.icon.setRelativePosition(3.0 / 4, 4.0 / 9);
	stock.buy.setRelativePosition(11.2 / 16, 4.1 / 9);
	stock.setCost(100.f); 
	stock.setPassiveModifier(1.f); 
}

void clickerBrain::click()
{
	
}

returnFrame * clickerBrain::update(sf::Event event)
{
	//Wiping and intialization for the new frame
	newFrame.frame.clear(sf::Color::White); 
	newFrame.value = 0;
	frameCount.add(); 
	newFrame.frame.draw(clickButton);
	Cursor.updatePos();
	moneyText.setString(std::to_string(money)); 
	managerCost.setString(std::to_string(manager.getCost()));
	stockCost.setString(std::to_string(stock.getCost()));
	money = money + (passiveValue/framesPerTic);

	//Cursor and Mouse
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		Cursor.pressed();
		if (clickButton.getGlobalBounds().contains(Cursor.getPosition()))
		{
			if (clickButton.pressed(true))
			{
				money += clickValue;
			}
		}
		else
		{
			clickButton.released();
		}
		for (auto i = modifierList.begin(); i != modifierList.end(); i++)
		{
			if ((*i)->buy.getGlobalBounds().contains(Cursor.getPosition()))
			{
				if ((*i)->buy.pressed(true))//if button wasn't pressed last frame execute tryBuy
				{
					(*i)->tryBuy(&money, &clickValue, &passiveValue);
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
		newFrame.frame.draw((*i)->buy); 
		newFrame.frame.draw((*i)->icon);
	}
	newFrame.frame.draw(managerCost);
	newFrame.frame.draw(stockCost);
	newFrame.frame.draw(moneyText); 
	newFrame.frame.draw(Cursor); 
	newFrame.frame.display();
	return &newFrame; 
	
}