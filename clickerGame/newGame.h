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
	sf::Font monoArial; 
	std::string input; 
	st backgroundImg;
	st backgroundBox;
	returnFrame newFrame;
	cursor Cursor;
	sf::Text text; 
	sf::Text title; 
	button enter; 
};


