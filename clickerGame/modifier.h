#pragma once
#include <SFML/Graphics.hpp>
#include <button.h>
#include <string.h>
class modifier 
{
public: 
	modifier(); 
	modifier(std::string); 
	void tryBuy(float* playerMoney, float* , float*); 
	button buy;
	st icon;
	void setCost(float); 
	void setClickModifier(float);
	void setPassiveModifier(float);
	float getCost();
	void setPosition(sf::Vector2f); 
	sf::Text costText; 
private:
	float clickValueModifier = 0;
	float passiveValueModifier = 0;
	float cost = 0;
};

