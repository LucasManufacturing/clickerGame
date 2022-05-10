#include "playerSave.h"
playerSave::playerSave()
{
	arial.loadFromFile("./fonts/arial.ttf"); 

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