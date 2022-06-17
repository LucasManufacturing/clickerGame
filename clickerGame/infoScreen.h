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
class infoScreen
{
public: 
	infoScreen(std::string, int); 
	returnFrame* update(sf::Vector2f);
private: 
	st text;
	cursor Cursor;
	button back; 
	int screenValue; 

	returnFrame newFrame;
};

