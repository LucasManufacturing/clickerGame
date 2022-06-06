#include <SFML/Graphics.hpp>
#include <clickerBrain.h>
#include <menu.h>
#include <newGame.h>
#include <iostream>
#include <loadSave.h>
#include <startMenu.h>

//add exit button to menus
//add back button 
//add help button
//add about button 
int main()
{
	
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Clicker Game", sf::Style::Fullscreen); //Creates the application 
	window.setMouseCursorVisible(false); //Hides OS mouse
	window.setFramerateLimit(30); //Sets frame limit to 30, important as time is kept by counting frames
	window.setVerticalSyncEnabled(true); //A rendering/display method which helps reduce screen tearing and artifacts
	window.requestFocus(); //Brings application to view 

	playerSave player; //intializes a playerSave object which stores game values. 
	startMenu startScreen;
	clickerBrain clickerScreen; //intializes a clickerBrain object which handles most gameplay features
	menu menuScreen(&player); //intializes a menu object which handles the menu screen
	newGame newScreen; //intializes a newGame object which handles the creation of a new game
	loadSave loadexample(&player);
	

	returnFrame *currentGameFrame = &returnFrame(); 
	returnFrame * menu = &returnFrame(); 

	st backdrop; 
	backdrop.setSprite("./sprites/backGround.png");
	backdrop.setPosition(0, 0);

	int keyCode; //holds the keycode value of a key pressed 
	int loading = -1;  //holds the state of the game, determines which screen is active| 0 = clickerBrain | 1 = menu | 2 = newGame

	while (window.isOpen()) //game runs whilst window is open
	{
		sf::Sprite gameFrame; //sprites to hold a new gameFrame frame
		sf::Sprite menuFrame; //sprites to hold a new menuFrame frame

		int mouseWheelMovement = 0;

		sf::Event event;
		keyCode = -1; 

		while (window.pollEvent(event))//Handles new computer events
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window.close(); //closes windows application 
				}
			/*	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))//if tab is pressed switch to menu or game object
				{
					loadexample.mouseHeld = true; 
					if (loading != 1)
					{
						loading = 1;
					}
					else
					{
						loading = 0;
					}
				}*/

				keyCode = event.key.code;
//				std::cout << keyCode << "\n"; 
			}
			if (event.type == sf::Event::MouseWheelMoved)
			{
				mouseWheelMovement = -event.mouseWheel.delta; 
			}
		}
		window.clear(); //clears the screen ready for new frame to display

		sf::Vector2f mousePos = { (float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y }; 
		mousePos = sf::Vector2f(( mousePos.x * (1920.f / window.getSize().x)), mousePos.y * (1080.f / window.getSize().y));//1920, 1080 comes from default framesize of clickerBrain.cpp, 

		if (player.saveName.empty() && loading <= 1)
		{
			gameFrame.setColor(sf::Color::Yellow);
			menu = startScreen.update(event, mousePos);
			menuFrame.setTexture(menu->frame.getTexture());
			loading = menu->value;
			gameFrame.scale((window.getSize().x / gameFrame.getLocalBounds().width), (window.getSize().y / gameFrame.getLocalBounds().height));
			menuFrame.scale((window.getSize().x / menuFrame.getLocalBounds().width), (window.getSize().y / menuFrame.getLocalBounds().height));
			window.draw(gameFrame);
			if (player.saveName.empty())
			{
				window.draw(backdrop);
			}
			window.draw(menuFrame);
		}
		switch (loading) //Switches to the active "screen" object
		{
		case 0: //Game
			gameFrame.setColor(sf::Color::White); //set background colour 
			currentGameFrame = clickerScreen.update( &player, mousePos); //Generates a new frame
			gameFrame.setTexture(currentGameFrame->frame.getTexture()); //stores frame for display
			loading = currentGameFrame->value; //sets the "screen" to be active next frame 
			gameFrame.scale((window.getSize().x / gameFrame.getLocalBounds().width), (window.getSize().y / gameFrame.getLocalBounds().height));//Scales the rendered frame to fit the window
			window.draw(gameFrame);//Draws the frame to the window 
			break; 
		case 1: //Menu 
			gameFrame.setColor(sf::Color(223, 232, 241, 125));
			gameFrame.setTexture(currentGameFrame->frame.getTexture());
			menu = menuScreen.update(event, mousePos);
			menuFrame.setTexture(menu->frame.getTexture());
			loading = menu->value; 
			gameFrame.scale((window.getSize().x / gameFrame.getLocalBounds().width), (window.getSize().y / gameFrame.getLocalBounds().height));
			menuFrame.scale((window.getSize().x / menuFrame.getLocalBounds().width), (window.getSize().y / menuFrame.getLocalBounds().height));
			window.draw(gameFrame);
			window.draw(menuFrame);
			break; 
		case 2: //new Game
			gameFrame.setColor(sf::Color(223, 232, 241, 125));
			gameFrame.setTexture(currentGameFrame->frame.getTexture());
			menu = newScreen.update(keyCode, mousePos, &player);
			menuFrame.setTexture(menu->frame.getTexture());
			loading = menu->value; 

			gameFrame.scale((window.getSize().x / gameFrame.getLocalBounds().width), (window.getSize().y / gameFrame.getLocalBounds().height));
			menuFrame.scale((window.getSize().x / menuFrame.getLocalBounds().width), (window.getSize().y / menuFrame.getLocalBounds().height));
			window.draw(gameFrame);
			if (player.saveName.empty())
			{
				window.draw(backdrop);
			}
			window.draw(menuFrame);
			break; 
		case 3: //loading
			gameFrame.setColor(sf::Color(223, 232, 241, 125));
			gameFrame.setTexture(currentGameFrame->frame.getTexture());
			menu = loadexample.update(mouseWheelMovement, mousePos, keyCode); 
			menuFrame.setTexture(menu->frame.getTexture()); 
			loading = menu->value; 
			menuFrame.scale((window.getSize().x / menuFrame.getLocalBounds().width), (window.getSize().y / menuFrame.getLocalBounds().height));
			gameFrame.scale((window.getSize().x / gameFrame.getLocalBounds().width), (window.getSize().y / gameFrame.getLocalBounds().height));
			window.draw(gameFrame); 
			if (player.saveName.empty())
			{
				window.draw(backdrop);
			}
			window.draw(menuFrame); 
			
			break;
		default: break;
		}


		
		window.display();//Displays frame to window 
	}

	return 0;
}