#include "loadSave.h"

loadSave::loadSave(playerSave *_player)
{
	playerPtr = _player;
	Cursor.loadButtonFromImage("./sprites/hand.png");

	view.reset(sf::FloatRect{ 0,0,900,250 });
	view.setViewport(sf::FloatRect{ 0.25, 0.25, 0.5, 0.25 });

	arial.loadFromFile("./fonts/arial.ttf");
	newFrame.frame.create(1920, 1080);
	for (const auto &fileIt : std::filesystem::directory_iterator( "saves" ))
	{
		std::string fileName = fileIt.path().filename().string(); 
		if (fileName.find("saveFile_") != std::string::npos)
		{
			fileName.erase(0, 9); 
			fileName.erase(fileName.end() - 4, fileName.end());
			saves.push_back(fileName); 
		}
	}

	for (auto i = saves.begin(); i != saves.end(); i++)
	{
		int index = std::distance(saves.begin(), i);

		loadBox _loadBox;
		_loadBox.loadButton.loadButtonFromImage("./sprites/loadBox.png"); 
		_loadBox.loadName.setString((*i)); 
		_loadBox.loadName.setFont(arial);
		_loadBox.loadName.setCharacterSize(30);
		_loadBox.loadName.setFillColor(sf::Color::Red); 

		_loadBox.loadButton.scale(3.f, 1);
		_loadBox.setPosition(sf::Vector2f{ 0.f, (index * 50.f) }); 

		loadBoxes.push_back(_loadBox); 
		std::cout << index << *i << "\n"; 
	}
}

returnFrame* loadSave::update(int _mouseWheelMovement, sf::Vector2f _mousePos)
{

	Cursor.setPosition(_mousePos); 
	newFrame.frame.clear(sf::Color::Transparent);
	newFrame.value = 3; 
	view.move(0, _mouseWheelMovement * 10);
	viewY = viewY + (_mouseWheelMovement * 10); 
	sf::Vector2f viewPos = view.getSize(); 

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !mouseHeld)
	{
		Cursor.pressed();
		for (auto i = loadBoxes.begin(); i != loadBoxes.end(); i++)
		{
			//checks to see if current loadBox is in view of scrollbox
			if (i->loadButton.getGlobalBounds().intersects(sf::FloatRect{0.f,(float)viewY,viewPos.x, viewPos.y}))
			{
				sf::FloatRect scrollBoxBounds = (i)->loadButton.getGlobalBounds();
				scrollBoxBounds = { 480 + scrollBoxBounds.left, 270 + scrollBoxBounds.top - viewY, scrollBoxBounds.width, scrollBoxBounds.height }; //translates the bounding boxes, so it matches with the displayed boxes

				if (scrollBoxBounds.contains(Cursor.getPosition()))
				{

					i->loadButton.pressed();
					playerPtr->loadFile(i->loadName.getString());
					newFrame.value = 0;
					mouseHeld = true;
				}
				else
				{
					(i)->loadButton.released();
				}
			}
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false && mouseHeld)
	{
		mouseHeld = false; 
	}
	else
	{
		Cursor.released(); 
		for (auto i = loadBoxes.begin(); i != loadBoxes.end(); i++)
		{
			i->loadButton.released(); 
		}
	}

	newFrame.frame.setView(view);
	//Draws all the boxes 
	for (auto i = loadBoxes.begin(); i != loadBoxes.end(); i++)
	{
		newFrame.frame.draw(i->loadButton);
		newFrame.frame.draw(i->loadName);
	}
	newFrame.frame.setView(newFrame.frame.getDefaultView()); 
	
	newFrame.frame.draw(Cursor); 
	newFrame.frame.display(); 

	return &newFrame;
}

void loadBox::setPosition(sf::Vector2f _pos)
{
	loadButton.setPosition(_pos.x, _pos.y);
	loadName.setPosition(_pos.x + 30, _pos.y + 10); 
}
