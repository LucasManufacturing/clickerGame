#pragma once
#include <button.h>
#include <spriteTools.h>
#include <filesystem>
#include <returnFrame.h>
#include <cursor.h>
#include <playerSave.h>
#include <iostream>
#include <fstream>
class newGame
{
public:
	returnFrame * update(int, sf::Vector2f, playerSave *);
	newGame();
	void createGame(playerSave *); 
private:
	std::ofstream writeFile; 
	sf::Font arial; 
	std::string input; 
	st backgroundImg;
	st backgroundBox;
	returnFrame newFrame;
	cursor Cursor;
	sf::Text text; 
};


