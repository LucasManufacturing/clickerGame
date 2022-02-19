#pragma once
#include <button.h>
#include <iostream>
//Child of button.h with an added updatePos() function to set position to mouse. 
class cursor : public button
{
public:
	cursor(); 
	void updatePos();
private:
};

