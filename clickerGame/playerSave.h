#pragma once
#include <modifier.h>
#include <list>
#include <fstream>
#include <filesystem>
class playerSave
{
public:
	playerSave(); 
	void loadFile(std::string);
	void newGame(std::string);
	void saveGame(); 

	modifier pencil;
	modifier scissors;
	modifier coffee;
	modifier thief;
	modifier stock;
	modifier manager;

	sf::Text title; 
	sf::Font arial;

	std::string saveName;

	std::list<modifier*> modifierList = {&pencil, &scissors, &coffee, &thief, &stock, &manager};
	float money = 0.0;
	float clickValue = 1.0;
	float passiveValue = 0.0; 

};

