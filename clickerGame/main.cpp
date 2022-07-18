#include <SFML/Graphics.hpp>
#include <clickerBrain.h>
#include <menu.h>
#include <newGame.h>
#include <iostream>
#include <loadSave.h>
#include <startMenu.h>
#include <infoScreen.h>

//implement background options/upgrades

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
	loadSave loadScreen(&player);
	infoScreen helpScreen("./sprites/howtoPlay.png", 5);
	infoScreen aboutScreen("./sprites/about.png", 6); 

	returnFrame *currentGameFrame = &returnFrame(); //Just explicitly intializes to eliminate possible crashes/error codes
	returnFrame *menu = &returnFrame(); //Just explicitly intializes to eliminate possible crashes/error codes

	st backdrop; 
	backdrop.setSprite("./sprites/backGround.png");
	backdrop.setPosition(0, 0);

	int keyCode; //holds the keycode value of a key pressed 
	int loading = -1;  //holds the state of the game, determines which screen is active| 0 = clickerBrain | 1 = menu | 2 = newGame

	while (window.isOpen()) //game runs whilst window is open
	{
		sf::Sprite gameFrame; //sprites to hold a new gameFrame frame
		sf::Sprite menuFrame; //sprites to hold any new menu frame

		int mouseWheelMovement = 0;

		sf::Event event;
		keyCode = -1; 

		while (window.pollEvent(event))//Handles new computer events
		{
			if (event.type == sf::Event::Closed)
			{
				loading = 4; //In "Screen Switch" the window will close
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					loading = 4;// In "Screen Switch" the window will close
				}
				keyCode = event.key.code;
			}
			if (event.type == sf::Event::MouseWheelMoved)
			{
				mouseWheelMovement = -event.mouseWheel.delta; 
			}
		}
		window.clear(); //clears the screen ready for new frame to display

		sf::Vector2f mousePos = { (float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y }; 
		mousePos = sf::Vector2f(( mousePos.x * (1920.f / window.getSize().x)), mousePos.y * (1080.f / window.getSize().y));//1920, 1080 comes from default framesize of clickerBrain.cpp||Will get relative mouse pos as all other screen natively render 1920,1080 

		if (player.saveName.empty() && loading <= 1)
		{
			gameFrame.setColor(sf::Color::Yellow);
			menu = startScreen.update(event, mousePos);//generates new frame
			menuFrame.setTexture(menu->frame.getTexture());
			loading = menu->value;
			gameFrame.scale((window.getSize().x / gameFrame.getLocalBounds().width), (window.getSize().y / gameFrame.getLocalBounds().height));//scale gameFrame up or down to fit display
			menuFrame.scale((window.getSize().x / menuFrame.getLocalBounds().width), (window.getSize().y / menuFrame.getLocalBounds().height));//scale menuFrame up or down to fit display
			window.draw(gameFrame); //draws first so it is background
			if (player.saveName.empty())
			{
				window.draw(backdrop);
			}
			window.draw(menuFrame);
		}

		//"Screen Switch"
		switch (loading) //Handles which screen scene should be loaded each frame. E.G the game screen or window screen. 
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
			gameFrame.scale((window.getSize().x / gameFrame.getLocalBounds().width), (window.getSize().y / gameFrame.getLocalBounds().height));//scale gameFrame up or down to fit display
			menuFrame.scale((window.getSize().x / menuFrame.getLocalBounds().width), (window.getSize().y / menuFrame.getLocalBounds().height));
			window.draw(gameFrame);//draw first for background
			window.draw(menuFrame);//draw last to appear ontop
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
			menu = loadScreen.update(mouseWheelMovement, mousePos, keyCode); 
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
		case 4: //Exit Application
			player.saveGame(); 
			window.close();//only expected place for application to legally close (apart from default case)
			break;
		case 5: //Help Page
			gameFrame.setColor(sf::Color(223, 232, 241, 125));
			gameFrame.setTexture(currentGameFrame->frame.getTexture());
			menu = helpScreen.update(mousePos);
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
		case 6: //About Page
			gameFrame.setColor(sf::Color(223, 232, 241, 125));
			gameFrame.setTexture(currentGameFrame->frame.getTexture());
			menu = aboutScreen.update(mousePos);
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
		default: 
			std::cout << "Error - Main.cpp Screen Switch has defaulted!"; //Requires some error notification as this switch should never default and may be hard to debug without this flag.
			player.saveGame();
			window.close();//closes window which will then close the process, without this, the default case would result in undefined behaviour likely freezing user's device.
			break; 
		}

		window.display();//Displays frame to window 
	}

	return 0;
}