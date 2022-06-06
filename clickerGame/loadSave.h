#pragma once
#include <returnFrame.h>
#include <counter.h>
#include <cursor.h>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <list>
#include <filesystem>
#include <button.h>
#include <spriteTools.h>
#include <playerSave.h>


class loadBox
{
public:
	void setPosition(sf::Vector2f); 
	button loadButton; 
	sf::Text loadName;
};

class loadSave
{
public:
	loadSave(playerSave*);
	returnFrame* update(int, sf::Vector2f, int);
	void findSaveFiles(); 

	st bar; 
	button knob; 
	button upArrow; 
	button downArrow; 

	//holds whether the user is dragging the scroll bar knob 
	bool dragging; 
	//turns true when user selects a save, and turns false when user enters the load menu
	bool exited = true;

	sf::Text title; 

	playerSave* playerPtr;
	bool mouseHeld = true; //To prevent clicking on save immediately after entering load screen, waits for user to release mouse. 
	cursor Cursor; 
	sf::View view; 
	returnFrame newFrame;
	std::list<std::string> saves;
	std::list<loadBox> loadBoxes;
	sf::Font arial;
	sf::Texture loadBoxTexture;
	int viewY = 0; 
};