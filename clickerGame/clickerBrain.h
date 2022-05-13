 #pragma once
#include <returnFrame.h>
#include <clickerBtn.h>
#include <counter.h>
#include <cursor.h>
#include <string.h>
#include <SFML/Graphics.hpp>

#include <list>
#include <playerSave.h>

class clickerBrain
{
public:
	clickerBrain(); 
	returnFrame * update(playerSave * _player, sf::Vector2f); 
	void click(); 
private:
	std::string to_dollar(float);
	returnFrame newFrame; 
	counter frameCount; 
	bool trial;
	cursor Cursor; 
	sf::Font arial; 

	button clickButton;
	sf::Text moneyText;

	sf::Text clickText; //money per click
	sf::Text passiveText; //money per second 

	button cog; 
	button save;
	st backGround; 



	

	int framesPerTic = 30; //should be one tic per second
};