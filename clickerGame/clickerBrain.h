#pragma once
#include <returnFrame.h>
#include <clickerBtn.h>
#include <counter.h>
#include <cursor.h>
#include <string.h>
#include <SFML/Graphics.hpp>

#include <list>
#include <playerSave.h>

class clickerBrain
{
public:
	clickerBrain(); 
	returnFrame * update(playerSave *, sf::Vector2f); 
	void click(); 
private:
	returnFrame newFrame; 
	counter frameCount; 
	bool trial;
	cursor Cursor; 
	sf::Font arial; 

	button clickButton;
	sf::Text moneyText;

	st cog; 
	st backGround; 

	modifier pencil;
	modifier scissors;
	modifier coffee;
	modifier thief;
	modifier stock; 
	modifier manager;

	std::list<modifier*> modifierList = {&pencil, &scissors, &coffee, &thief, &stock, &manager};

	int framesPerTic = 30; //should be one tic per second
};