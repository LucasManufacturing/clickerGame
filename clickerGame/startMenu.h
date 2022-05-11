#pragma once
#include <button.h>
#include <spriteTools.h>
#include <filesystem>
#include <returnFrame.h>
#include <cursor.h>
class startMenu
{
public:
	returnFrame * update(sf::Event, sf::Vector2f);
	startMenu();
private:

	button save;
	button Back;
	button load;
	button newGame;
	std::list<button*> buttonList = { &newGame, &load };
	st backgroundImg;
	st backgroundBox;
	returnFrame newFrame;
	cursor Cursor;
};


