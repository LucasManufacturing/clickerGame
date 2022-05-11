#include "button.h"
button::button(std::string path)
{
	loadButtonFromImage(path);
}
button::button() {}
void button::pressed() 
{
	sprite[0].texCoords = sf::Vector2f(textureSize.x / 2, 0.f);
	sprite[1].texCoords = sf::Vector2f(textureSize.x, 0.f);
	sprite[2].texCoords = sf::Vector2f(textureSize.x, textureSize.y);
	sprite[3].texCoords = sf::Vector2f(textureSize.x / 2, textureSize.y);
}
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
void button::released()
{
	activated = false; 
	sprite[0].texCoords = sf::Vector2f(0.f, 0.f);
	sprite[1].texCoords = sf::Vector2f(textureSize.x / 2, 0.f);
	sprite[2].texCoords = sf::Vector2f(textureSize.x / 2, textureSize.y);
	sprite[3].texCoords = sf::Vector2f(0.f, textureSize.y);
}

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
