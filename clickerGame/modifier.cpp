#include "modifier.h"
modifier::modifier(std::string iconPath)
{
	icon.setSprite(iconPath);
	icon.centre(); 
	
	buy.loadButtonFromImage("./sprites/greenBuy.png");
	buy.centre();

	costText.setOutlineColor(sf::Color::Black);
	costText.setOutlineThickness(1); 

	border = sf::VertexArray(sf::PrimitiveType::Quads, 4);
	//border[0].position(icon.getBounds);
	
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

void modifier::setPosition(sf::Vector2f pos)
{
	icon.setPosition(pos);
	buy.setPosition(pos.x + 160, pos.y); 
	costText.setPosition(pos.x - 180, pos.y - 20);
}