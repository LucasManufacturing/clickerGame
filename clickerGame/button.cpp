#include "button.h"
button::button(std::string path)
{
	loadButtonFromImage(path);
}
button::button() {}

//returns pressed state. 
bool button::getState()
{
	return activated;
}
//switches to right half of the button sprite
void button::pressed() 
{
	activated = true; 
	sprite[0].texCoords = sf::Vector2f(textureSize.x / 2, 0.f);
	sprite[1].texCoords = sf::Vector2f(textureSize.x, 0.f);
	sprite[2].texCoords = sf::Vector2f(textureSize.x, textureSize.y);
	sprite[3].texCoords = sf::Vector2f(textureSize.x / 2, textureSize.y);
}

//switches to right half of button sprite, returns whether button was previously clicked prior to call
bool button::pressed(bool check)
{
	bool newPress = false; 
	if (!activated)
	{
		sprite[0].texCoords = sf::Vector2f(textureSize.x / 2, 0.f);
		sprite[1].texCoords = sf::Vector2f(textureSize.x, 0.f);
		sprite[2].texCoords = sf::Vector2f(textureSize.x, textureSize.y);
		sprite[3].texCoords = sf::Vector2f(textureSize.x / 2, textureSize.y);
		activated = true; 
		newPress = true; 
	}
	return newPress;
}

//switches to left half of button sprite
void button::released()
{
	activated = false; 
	sprite[0].texCoords = sf::Vector2f(0.f, 0.f);
	sprite[1].texCoords = sf::Vector2f(textureSize.x / 2, 0.f);
	sprite[2].texCoords = sf::Vector2f(textureSize.x / 2, textureSize.y);
	sprite[3].texCoords = sf::Vector2f(0.f, textureSize.y);
}

//Accepts a relative or absolute path to image, and sets the texture for the button. If path is invalid a purple square is rendered as path holder. 
bool button::loadButtonFromImage(std::string path)
{
	if(setTexture(path))
	{
		sprite = sf::VertexArray(sf::PrimitiveType::Quads, 4);
		sprite[0].position = sf::Vector2f(0.f, 0.f);
		sprite[1].position = sf::Vector2f(textureSize.x / 2, 0.f);
		sprite[2].position = sf::Vector2f(textureSize.x / 2, textureSize.y);
		sprite[3].position = sf::Vector2f(0.f, textureSize.y);
		sprite[0].texCoords = sf::Vector2f(0.f, 0.f);
		sprite[1].texCoords = sf::Vector2f(textureSize.x / 2, 0.f);
		sprite[2].texCoords = sf::Vector2f(textureSize.x / 2, textureSize.y);
		sprite[3].texCoords = sf::Vector2f(0.f, textureSize.y);
	}
return !imgError;
}
