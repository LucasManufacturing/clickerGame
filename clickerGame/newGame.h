#pragma once
#include <button.h>
#include <spriteTools.h>
#include <returnFrame.h>
#include <cursor.h>
#include <playerSave.h>
#include <iostream>
class newGame
{
public:
	returnFrame * update(int, sf::Vector2f, playerSave *);
	newGame();

private:
	sf::Font arial; 
	std::string input; 
	st backgroundImg;
	st backgroundBox;
	returnFrame newFrame;
	cursor Cursor;
	sf::Text text; 
};


