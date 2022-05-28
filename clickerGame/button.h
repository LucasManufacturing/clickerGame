#pragma once
#include <spriteTools.h>
#include <string.h>
#include <iostream>
//Child of spriteTools, used for a button loaded from a single texture with two graphical states, as well as state buttons pressed() and released()
class button : public st	
{
public: 
	button(); 
	button(std::string path); 
	//toggles the texture view to the pressed button
	void pressed(); 
	bool pressed(bool);
	//toggles the texture view to the released button
	void released(); 
	
	//image must have released button on left hand side and pressed button on righthand side divided in half width ways. 
	bool loadButtonFromImage(std::string);
	//gets whether the button is pressed or released. True is pressed, False is released. 
	bool getState();
private:
	bool activated;
};

