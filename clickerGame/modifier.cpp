#include "modifier.h"
modifier::modifier(std::string iconPath)
{
	icon.setSprite(iconPath);
	icon.centre(); 
	
	buy.loadButtonFromImage("./sprites/greenBuy.png");
	buy.centre();

	redBuy.loadButtonFromImage("./sprites/redBuy.png");
	redBuy.centre(); 

	costText.setOutlineColor(sf::Color::Black);
	costText.setOutlineThickness(1); 


	
}
modifier::modifier()
{

}
float modifier::getCost()
{
	return cost; 
}
void modifier::tryBuy(float* playerMoney, float* _clickValue, float* _passiveValue)
{
	if (*playerMoney >= cost)
	{
		*playerMoney = *playerMoney - cost; 
		*_clickValue = *_clickValue + clickValueModifier;
		*_passiveValue = *_passiveValue + passiveValueModifier; 
		cost = cost + (cost / 2.f); 
	}
}

void modifier::setCost(float _float)
{
	cost = _float;
}

void modifier::setClickModifier(float _float)
{
	clickValueModifier = _float; 
	modifierText.setString("+" + std::to_string((int)_float) + "/click");
}

void modifier::setPassiveModifier(float _float)
{
	passiveValueModifier = _float;
	modifierText.setString("+" + std::to_string((int)_float) + "/sec");
}

void modifier::setPosition(sf::Vector2f pos)
{
	icon.setPosition(pos);
	buy.setPosition(pos.x + 160, pos.y); 
	redBuy.setPosition(pos.x + 160, pos.y); 
	costText.setPosition(pos.x + 103, pos.y - 70);
	modifierText.setPosition(pos.x - 200, pos.y - 20);
}