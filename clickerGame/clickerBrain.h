#pragma once
#include <returnFrame.h>
#include <clickerBtn.h>
#include <counter.h>
#include <cursor.h>
#include <SFML/Graphics.hpp>
class clickerBrain
{
public:
	clickerBrain(); 
	returnFrame * update(sf::Event); 
private:
	returnFrame newFrame; 
	counter frameCount; 
	clickerBtn clickButton; 
	cursor Cursor; 
};