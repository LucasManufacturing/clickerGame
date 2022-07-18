#include "spriteTools.h"
void st::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	if (!imgError)//only if no img errors to load texture, to displayed magenta square no texture must be applied. 
	{
		states.texture = &texture;
	}
	target.draw(sprite, states);
}

bool st::setTexture(std::string path) //returns true if texture was loaded successfully
{
	sprite.clear();
	if (!texture.loadFromFile(path)) //if load files a 50x50 magenta square will be rendered instead 
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
		imgError = false; 
	}
	return !imgError; 
}

bool st::setSprite(std::string path) //returns true if sprite was set successfully
{
	sprite.clear();
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
		sprite = sf::VertexArray(sf::PrimitiveType::Quads, 4);
		sprite[0].position = sf::Vector2f(0.f, 0.f);
		sprite[1].position = sf::Vector2f(textureSize.x, 0.f);
		sprite[2].position = sf::Vector2f(textureSize.x, textureSize.y);
		sprite[3].position = sf::Vector2f(0.f, textureSize.y);
		sprite[0].texCoords = sf::Vector2f(0.f, 0.f);
		sprite[1].texCoords = sf::Vector2f(textureSize.x, 0.f);
		sprite[2].texCoords = sf::Vector2f(textureSize.x, textureSize.y);
		sprite[3].texCoords = sf::Vector2f(0.f, textureSize.y);
		imgError = false;
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
sf::FloatRect st::getBounds() //get size bassically
{
	return sf::FloatRect{ 0, 0, ((sprite[1].position.x - sprite[0].position.x) * getScale().x), ((sprite[2].position.y - sprite[0].position.y) * getScale().y) };
}

void st::setOrigin(sf::Vector2f pos) //Sets origin (point where SFML treats the object as existing at) 
{
	origin = pos;
	sprite[0].position = sf::Vector2f(sprite[0].position.x - pos.x, sprite[0].position.y - pos.y);
	sprite[1].position = sf::Vector2f(sprite[1].position.x - pos.x, sprite[1].position.y - pos.y);
	sprite[2].position = sf::Vector2f(sprite[2].position.x - pos.x, sprite[2].position.y - pos.y);
	sprite[3].position = sf::Vector2f(sprite[3].position.x - pos.x, sprite[3].position.y - pos.y);
}
void st::setRelativeOrigin(sf::Vector2f pos) //Sets origin as a fraction of the sprite size (point where SFML treats the object as existing at) 
{
	setOrigin(sf::Vector2f{ (sprite[1].position.x - sprite[0].position.x) * pos.x, (sprite[2].position.y - sprite[0].position.y) * pos.y });
}
void st::centre() //centres origin
{
	setOrigin(sf::Vector2f( (sprite[1].position.x - sprite[0].position.x) / 2, (sprite[2].position.y - sprite[0].position.y) / 2 ));
}

void st::setRelativePosition(sf::Vector2f pos) //sets position of sprite by using a fraction of the display
{

	setPosition(1920.f * pos.x, 1080.f * pos.y);
}

void st::setRelativePosition(float x, float y)  //sets position of sprite by using a fraction of the display
{
	setPosition(1920.f * x, 1080.f * y);
}