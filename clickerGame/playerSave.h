#pragma once
#include <modifier.h>
#include <list>
class playerSave
{
public:
	playerSave(); 

	modifier pencil;
	modifier scissors;
	modifier coffee;
	modifier thief;
	modifier stock;
	modifier manager;
	sf::Font arial;
	std::list<modifier*> modifierList = {&pencil, &scissors, &coffee, &thief, &stock, &manager};
	float money = 0.0;
	float clickValue = 1;
	float passiveValue = 0; 

};

