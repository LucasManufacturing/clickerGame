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
	playerSave* playerPtr;
	bool mouseHeld = true; 
	cursor Cursor; 
	sf::View view; 
	returnFrame* update(int, sf::Vector2f);
	returnFrame newFrame;
	std::list<std::string> saves;
	std::list<loadBox> loadBoxes;
	sf::Font arial;
	sf::Texture loadBoxTexture;
	int viewY = 0; 
};