#pragma once
#include <returnFrame.h>
#include <clickerBtn.h>
#include <counter.h>
#include <cursor.h>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <modifier.h>
#include <list>

class clickerBrain
{
public:
	clickerBrain(); 
	returnFrame * update(sf::Event); 
	void click(); 
private:
	returnFrame newFrame; 
	counter frameCount; 
	
	cursor Cursor; 
	float money;

	float clickValue = 1; 
	float passiveValue = 0; 
	sf::Text moneyText; 
	sf::Text managerCost;
	sf::Text stockCost;
	sf::Font arial; 

	button clickButton;

	modifier stock; 
	modifier manager;

	std::list<modifier*> modifierList = {&stock, &manager};

	int framesPerTic = 30; //should be one tic per second
};