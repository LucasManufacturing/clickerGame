#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class st : public sf::Transformable, public sf::Drawable
{
public:
	sf::FloatRect getGlobalBounds();
	sf::FloatRect getBounds();
	void setOrigin(sf::Vector2f);
	void setRelativeOrigin(sf::Vector2f);
	void centre();
	bool setTexture(std::string path);
	void setRelativePosition(sf::Vector2f); 
	void setRelativePosition(float, float); 
	bool setSprite(std::string); 
protected:
	sf::Vector2u textureSize;
	bool imgError = false; 
	sf::Vector2f origin;
	sf::VertexArray sprite;
	sf::Texture texture;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
};

