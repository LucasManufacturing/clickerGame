#include "spriteTools.h"
void st::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if (!imgError)
	{
		states.texture = &texture;
	}

	target.draw(sprite, states);
}

bool st::setTexture(std::string path) //returns true if texture was loaded successfully
{
	if (!texture.loadFromFile(path))
	{
		std::cout << "\nError loading image:" << path << "\n";
		texture.create(1, 1);
		sprite = sf::VertexArray(sf::PrimitiveType::Quads, 4);
		sprite[0].position = sf::Vector2f(0.f, 0.f);
		sprite[1].position = sf::Vector2f(50.f, 0.f);
		sprite[2].position = sf::Vector2f(50.f, 50.f);
		sprite[3].position = sf::Vector2f(0.f, 50.f);
		sprite[0].color = sf::Color::Magenta;
		sprite[1].color = sf::Color::Magenta;
		sprite[2].color = sf::Color::Magenta;
		sprite[3].color = sf::Color::Magenta;
		imgError = true; 
	}
	else
	{
		std::cout << "\nImage: " << path << " loaded\n";
		textureSize = texture.getSize();
	}
	return !imgError; 
}
sf::FloatRect st::getGlobalBounds()//gets hitbox of sprite, returns a rectangle which should encompass drawn sprite
{
	sf::Transform transform = getTransform();
	sf::Vector2f topLeft = transform.transformPoint(sprite[0].position);
	float width = (sprite[1].position.x - sprite[0].position.x) * getScale().x;
	float height = (sprite[2].position.y - sprite[0].position.y) * getScale().y;
	return sf::FloatRect{ topLeft.x, topLeft.y, width, height };
}
sf::FloatRect st::getBounds()
{
	return sf::FloatRect{ 0, 0, ((sprite[1].position.x - sprite[0].position.x) * getScale().x), ((sprite[2].position.y - sprite[0].position.y) * getScale().y) };
}

void st::setOrigin(sf::Vector2f pos)
{
	origin = pos;
	sprite[0].position = sf::Vector2f(sprite[0].position.x - pos.x, sprite[0].position.y - pos.y);
	sprite[1].position = sf::Vector2f(sprite[1].position.x - pos.x, sprite[1].position.y - pos.y);
	sprite[2].position = sf::Vector2f(sprite[2].position.x - pos.x, sprite[2].position.y - pos.y);
	sprite[3].position = sf::Vector2f(sprite[3].position.x - pos.x, sprite[3].position.y - pos.y);
}
void st::setRelativeOrigin(sf::Vector2f pos)
{
	setOrigin(sf::Vector2f{ (sprite[1].position.x - sprite[0].position.x) * pos.x, (sprite[2].position.y - sprite[0].position.y) * pos.y });
}
void st::centre()
{
	setOrigin(sf::Vector2f{ (sprite[1].position.x - sprite[0].position.x) / 2, (sprite[2].position.y - sprite[0].position.y) / 2 });
}
