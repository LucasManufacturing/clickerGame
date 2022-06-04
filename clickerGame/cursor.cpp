#include "cursor.h"

cursor::cursor()
{
	loadButtonFromImage("./sprites/hand.png"); 
	setRelativeOrigin(sf::Vector2f{ 25.f / 64.f, 7.f / 64.f });//puts origin on cursor's finger

}

void cursor::updatePos()
{
	setPosition((float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y);
}
