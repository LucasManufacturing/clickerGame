#pragma once
#include <returnFrame.h>
#include <counter.h>
#include <cursor.h>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <list>
#include <filesystem>
class loadSave
{
public: 
	loadSave(); 
	returnFrame update(); 
	std::list<std::string> saves; 
};

