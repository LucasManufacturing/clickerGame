
#include "newGame.h"
newGame::newGame()
{
	arial.loadFromFile("./fonts/arial.ttf");

	newFrame.frame.create(1920, 1080);
	Cursor.loadButtonFromImage("./sprites/hand.png");
	backgroundImg.setSprite("./sprites/newGameMenu.png");
	backgroundImg.centre();
	backgroundImg.setRelativePosition(1.f / 2, 1.f / 2);

	backgroundBox.setSprite("./sprites/smallBox.png");
	backgroundBox.centre();
	backgroundBox.setRelativePosition(1.f / 2, 1.f / 2);

	enter.loadButtonFromImage("./sprites/enter.png"); 
	enter.setPosition(1214, 528);

	title.setPosition(670, 450); 
	title.setFont(arial);
	title.setFillColor(sf::Color::White);
	title.setCharacterSize(50); 
	title.setString("Enter a New Game Name");

	text.setFont(arial); 
	text.setCharacterSize(60);
	text.setFillColor(sf::Color::Black);
	text.setPosition(615, 540); 
	
}

returnFrame * newGame::update(int _keyCode, sf::Vector2f mousePos, playerSave * _player)
{
	int keyCode = _keyCode; 
	//Wiping and intialization for the new frame
	newFrame.frame.clear(sf::Color::Transparent);
	newFrame.value = 2;

	Cursor.setPosition(mousePos); //Updates Cursor Position 
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) //Detects a left button mouse click and handles clickable events (buttons)
	{
		Cursor.pressed();
		if (enter.getGlobalBounds().contains(Cursor.getPosition()))
		{
			enter.pressed();
			keyCode = 58; //keyCode 58 corresponds with the enter key, to eliminate possible duplication of files setting keycode to 58 will mean only one stub handles the explicit creation of a game. 
		}
		else
		{
			enter.released();
		}
	}
	else
	{
		Cursor.released();
		enter.released();
	}

		switch (keyCode) //Translates SFML key code to corresponding character or function.
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
		case 58: //Enter key pressed
			_player->newGame(input); //save game is created using user inputed string. 
			input.clear();
			newFrame.value = 0;
			break;
		case 59: //backspace
			if (!input.empty())//checks to see if input is empty
			{
				input.erase(input.end() - 1); //deletes last character by going to the position before the string terminator
			}
			break;
		default: break;
		}

		//ensures input does not go too long and over run it's text box. 
		if (input.length() > 14)
		{
			input.erase(input.begin()+14, input.end()); //deletes all characters after 15th 
		}
		if (keyCode != -1)
		{
			text.setString(input); 
			std::cout << input << "\n";
		}



	
	newFrame.frame.draw(backgroundImg);
	newFrame.frame.draw(backgroundBox);
	newFrame.frame.draw(enter);
	newFrame.frame.draw(text); 
	newFrame.frame.draw(title);
	newFrame.frame.draw(Cursor);
	newFrame.frame.display();
	return &newFrame;

}
