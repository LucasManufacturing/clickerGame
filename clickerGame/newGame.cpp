
#include "newGame.h"
newGame::newGame()
{
	arial.loadFromFile("./fonts/arial.ttf");

	newFrame.frame.create(1920, 1080);
	Cursor.loadButtonFromImage("./sprites/hand.png");
	backgroundImg.setSprite("./sprites/smallBackground.png");
	backgroundImg.centre();
	backgroundImg.setRelativePosition(1.f / 2, 1.f / 2);

	backgroundBox.setSprite("./sprites/smallBox.png");
	backgroundBox.centre();
	backgroundBox.setRelativePosition(1.f / 2, 1.f / 2);

	text.setFont(arial); 
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::White);
	text.setPosition(900, 540); 
	
}

returnFrame * newGame::update(int keyCode, sf::Vector2f mousePos, playerSave * _player)
{
	//Wiping and intialization for the new frame
	newFrame.frame.clear(sf::Color::Transparent);
	newFrame.value = 2;
	Cursor.setPosition(mousePos);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		Cursor.pressed();
	}
	else
	{
		Cursor.released();
	}

	switch (keyCode)
	{
	case 0:
		input.append("A");
		break;
	case 1:
		input.append("B");
		break;
	case 2:
		input.append("C");
		break;
	case 3:
		input.append("D");
		break;
	case 4:
		input.append("E");
		break;
	case 5:
		input.append("F");
		break;
	case 6:
		input.append("G");
		break;
	case 7:
		input.append("H");
		break;
	case 8:
		input.append("I");
		break;
	case 9:
		input.append("J");
		break;
	case 10:
		input.append("K");
		break;
	case 11:
		input.append("L");
		break;
	case 12:
		input.append("M");
		break;
	case 13:
		input.append("N");
		break;
	case 14:
		input.append("O");
		break;
	case 15:
		input.append("P");
		break;
	case 16:
		input.append("Q");
		break;
	case 17:
		input.append("R");
		break;
	case 18:
		input.append("S");
		break;
	case 19:
		input.append("T");
		break;
	case 20:
		input.append("U");
		break;
	case 21:
		input.append("V");
		break;
	case 22:
		input.append("W");
		break;
	case 23:
		input.append("X");
		break;
	case 24:
		input.append("Y");
		break;
	case 25:
		input.append("Z");
		break;
	case 57:
		input.append(" ");
		break;
	case 58:
		createGame(_player); 
		newFrame.value = 1; 
		break;
	case 59: //backspace
		if (input.end() != input.begin())
		{
			input.erase(input.end() - 1);
		}
		break;
	default: break;
	}
	if (keyCode != -1)
	{
		text.setString(input); 
		std::cout << input << "\n";
	}

	
	newFrame.frame.draw(backgroundImg);
	newFrame.frame.draw(backgroundBox);
	newFrame.frame.draw(text); 
	newFrame.frame.draw(Cursor);
	newFrame.frame.display();
	return &newFrame;

}
void newGame::createGame(playerSave* _player)
{
	std::string fileLocation = "saves\\saveFile_"; 
	fileLocation.append(input); 
	fileLocation.append(".txt"); 
	writeFile.open(fileLocation);
	writeFile << "@" << _player->money << "#\n"; 
	writeFile << "@" << _player->clickValue << "#\n";
	writeFile << "@" << _player->passiveValue << "#\n";
	for (auto i = _player->modifierList.begin(); i != _player->modifierList.end(); i++)
	{
		writeFile << "@" << std::to_string((*i)->getCost()) << "#\n";
	}
	writeFile.close(); 
}