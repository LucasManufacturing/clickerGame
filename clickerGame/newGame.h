#pragma once
#include <button.h>
#include <spriteTools.h>
#include <filesystem>
#include <returnFrame.h>
#include <cursor.h>
class newGame
{
public:
	returnFrame * update(int, sf::Vector2f);
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


