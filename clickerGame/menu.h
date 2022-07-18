#pragma once
#include <button.h>
#include <spriteTools.h>
#include <filesystem>
#include <returnFrame.h>
#include <cursor.h>
#include <playerSave.h>
class menu
{
public:
	returnFrame * update(sf::Event, sf::Vector2f); 
	menu(playerSave*); 
private:
	sf::Font monoArial; 

	playerSave* playerPTR;

	button back; 
	button exit;
	button load; 
	button newGame; 
	button help; 
	button about; 
	st backgroundImg; 
	st backgroundBox; 
	returnFrame newFrame; 
	cursor Cursor;
	sf::Text name;
};

