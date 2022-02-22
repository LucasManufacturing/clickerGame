#include "modifier.h"
modifier::modifier(std::string iconPath)
{
	icon.setSprite(iconPath);
	buy.loadButtonFromImage("./sprites/greenBuy.png");

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
}

void modifier::setPassiveModifier(float _float)
{
	passiveValueModifier = _float;
}