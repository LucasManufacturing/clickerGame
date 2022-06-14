#include "loadSave.h"

loadSave::loadSave(playerSave *_player)
{
	playerPtr = _player;

	bar.setSprite("./sprites/scrollbar.png");
	bar.setScale(1.f, 1.08);
	bar.setPosition(1440, 270);

	knob.loadButtonFromImage("./sprites/scrollknob.png");
	knob.setScale(1.5, 1.5); 
	knob.centre();
	knob.setPosition(1500, 400);

	upArrow.loadButtonFromImage("./sprites/scrollarrow.png");
	upArrow.setPosition(1440, 258);
	upArrow.scale(2.f, 1.5);

	downArrow.loadButtonFromImage("./sprites/scrollarrow.png");
	downArrow.rotate(180.0);
	downArrow.setOrigin(sf::Vector2f{ 0.f, 0.f });
	downArrow.setPosition(1440, 560);
	downArrow.scale(2.f, 1.5);

	title.setFont(arial);
	title.setStyle(sf::Text::Bold); 
	title.setOutlineColor(sf::Color::Black); 
	title.setOutlineThickness(5);
	title.setCharacterSize(80);
	title.setString("Select a Save to Load");
	title.setPosition(575, 160);

	back.loadButtonFromImage("./sprites/back.png");
	back.setScale(3.f, 3.f);
	back.centre();
	back.setPosition(960, 800); 

	view.reset(sf::FloatRect{ 0,0,900,250 });
	view.setViewport(sf::FloatRect{ 0.25, 0.25, 0.5, 0.25 });

	arial.loadFromFile("./fonts/arial.ttf");
	newFrame.frame.create(1920, 1080);
}

//handles actions & generates a new frame for loading a save menu. 
returnFrame* loadSave::update(int _mouseWheelMovement, sf::Vector2f _mousePos, int _keyCode)
{
	float mousePosYchange = (_mousePos.y - Cursor.getPosition().y) * 3; 
	Cursor.setPosition(_mousePos); 
	newFrame.frame.clear(sf::Color::Transparent);
	newFrame.value = 3; 
	view.move(0, _mouseWheelMovement * 10);
	viewY = viewY + (_mouseWheelMovement * 10); 
	sf::Vector2f viewPos = view.getSize(); 

	if (exited)
	{
		findSaveFiles(); 
		exited = false;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !mouseHeld)
	{
		Cursor.pressed();
		//If user clicks "Back" user will be sent to the game Screen, code located in clickerBrain.h & clickerBrain.cpp
		if (back.getGlobalBounds().contains(Cursor.getPosition()))
		{
			back.pressed(true);
			newFrame.value = 0;
		}
		else
		{
			back.released();
		}
		if (knob.getGlobalBounds().contains(Cursor.getPosition())) 
		{
			knob.pressed();
			dragging = true; 
		}
		else
		{
			knob.released();
		}

		if (upArrow.getGlobalBounds().contains(Cursor.getPosition()))
		{
			upArrow.pressed();
			viewY = viewY - 5; 
			view.move(0.f, -5.f);
		}
		else
		{
			upArrow.released();
		}

		if (downArrow.getGlobalBounds().contains(Cursor.getPosition()))
		{
			downArrow.pressed();
			viewY = viewY + 5;
			view.move(0.f, 5.f);
		}
		else
		{
			downArrow.released();
		}

		for (auto i = loadBoxes.begin(); i != loadBoxes.end(); i++)
		{
			//checks to see if current loadBox is in view of the current scroll box
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
					exited = true;
				}
				else
				{
					(i)->loadButton.released();
				}
			}
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) == false && mouseHeld) //stub asserts when user is choosing an option
	{
		mouseHeld = false; 
	}
	else //if left click not pressed, release all buttons 
	{
		Cursor.released(); 
		for (auto i = loadBoxes.begin(); i != loadBoxes.end(); i++)
		{
			i->loadButton.released(); 
		}
		knob.released();
		downArrow.released();
		upArrow.released();
		dragging = false; 
	}

	if (dragging)
	{
		viewY = viewY + mousePosYchange;
		view.move(0.f, mousePosYchange);	
	}

	if (viewY > loadBoxes.size()*50.f -250) //Checks to see if view is too far down, if it is it will bring it back to the end
	{
		float a = (loadBoxes.size()*50.f - 250) - viewY;//a is a temporary value holder, it holds the distance from the view position and the end of the load boxes
		view.move(0.f, a); 
		viewY = viewY + a; 
	}
	if (viewY < 0) //Checks to see if view is too far up, if it is it will bring it back to it's start, 
	{
		view.move(0.f, -viewY);
		viewY = 0; 
	}


	//updates knob position
	knob.setPosition(1445.f, 293 + (230 * (viewY / (loadBoxes.size()*50.f - 250))));

	switch (_keyCode)
	{
	case 60:
		newFrame.value = 1; 
	}

	newFrame.frame.setView(view);
	//Draws all the boxes 
	for (auto i = loadBoxes.begin(); i != loadBoxes.end(); i++)
	{
		newFrame.frame.draw(i->loadButton);
		newFrame.frame.draw(i->loadName);
	}
	newFrame.frame.setView(newFrame.frame.getDefaultView()); 
	
	newFrame.frame.draw(title);
	newFrame.frame.draw(bar);
	newFrame.frame.draw(knob);
	newFrame.frame.draw(upArrow);
	newFrame.frame.draw(downArrow);
	newFrame.frame.draw(back);
	newFrame.frame.draw(Cursor); 
	newFrame.frame.display(); 

	return &newFrame;
}

//executes each time the user enters into the loading a save menu.
void loadSave::findSaveFiles()
{
	for (const auto &fileIt : std::filesystem::directory_iterator("saves"))
	{
		std::string fileName = fileIt.path().filename().string();
		if ((fileName.find("saveFile_") != std::string::npos) && fileName.length() <= 29) //Will only load valid saves which include the prefix saveFile_ & whose save name is less than 17 characters.
		{
			fileName.erase(0, 9);
			fileName.erase(fileName.end() - 4, fileName.end());
			saves.push_back(fileName);
		}
	}

	for (auto i = saves.begin(); i != saves.end(); i++)
	{
		int index = std::distance(saves.begin(), i); //finds integer value of the iterator position 

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

//simple function to change the position of load boxes. 
void loadBox::setPosition(sf::Vector2f _pos)
{
	loadButton.setPosition(_pos.x, _pos.y);
	loadName.setPosition(_pos.x + 30, _pos.y + 10); 
}
