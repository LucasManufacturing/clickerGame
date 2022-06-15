#include "playerSave.h"
playerSave::playerSave()
{
	arial.loadFromFile("./fonts/arial.ttf"); 

	pencil = modifier("./sprites/pencil.png");
	pencil.setPosition(sf::Vector2f(416, 348));
	pencil.setCost(25.f);
	pencil.setClickModifier(1.f);

	scissors = modifier("./sprites/scissors.png");
	scissors.setPosition(sf::Vector2f(416, 540));
	scissors.setCost(50.f);
	scissors.setClickModifier(5.f);

	coffee = modifier("./sprites/coffee.png");
	coffee.setPosition(sf::Vector2f(416, 732));
	coffee.setCost(100.f);
	coffee.setClickModifier(15.f);

	thief = modifier("./sprites/thief.png");
	thief.setPosition(sf::Vector2f(1376, 348));
	thief.setCost(75.f);
	thief.setPassiveModifier(1.f);

	stock = modifier("./sprites/stocks.png");
	stock.setPosition(sf::Vector2f(1376, 540));
	stock.setCost(150.f);
	stock.setPassiveModifier(5.f);

	manager = modifier("./sprites/manager.png");
	manager.setPosition(sf::Vector2f(1376, 732));
	manager.setCost(300.f);
	manager.setPassiveModifier(10.f);

	for (auto i = modifierList.begin(); i != modifierList.end(); i++)
	{
		(*i)->icon.setScale(1.5, 1.5);
		(*i)->buy.setScale(2.0, 1.5);
		(*i)->redBuy.setScale(2.0, 1.5);
		(*i)->costText.setFont(arial);
		(*i)->costText.setCharacterSize(40);
		(*i)->modifierText.setFont(arial);
		(*i)->modifierText.setCharacterSize(40);
		(*i)->costText.setFillColor(sf::Color::White);
	}
}

void playerSave::loadFile(std::string filename)
{
	std::string path = "saves\\saveFile_" + filename + ".txt"; 
	saveName = filename; 
	std::ifstream file(path);
	std::string line; 
	float holder;
	int count = 0;
	while (std::getline(file, line))
	{
		line.erase(line.begin());
		line.pop_back();
		holder = std::stof(line);
		switch (count)
		{
		case 0: 
			money = holder;
			break;
		case 1: 
			clickValue = holder;
			break;
		case 2: 
			passiveValue = holder; 
		case 3: 
			pencil.setCost(holder);
			break;
		case 4:
			scissors.setCost(holder);
			break;
		case 5:
			coffee.setCost(holder);
			break;
		case 6:
			thief.setCost(holder);
			break;
		case 7:
			stock.setCost(holder);
			break;
		case 8:
			manager.setCost(holder);
			break;
		default:
			break;
		}
		count++;
		
	}
	file.close();
}

void playerSave::saveGame()
{
	if (!saveName.empty()) //Won't attempt to save without a saveName. 
	{
		std::string path = "saves\\saveFile_";
		path.append(saveName);
		path.append(".txt");
		std::ofstream file(path);
		if (std::filesystem::is_empty(std::filesystem::path{ path }) == false)
		{
			file.clear();
		}
		file << "@" << money << "#\n";
		file << "@" << clickValue << "#\n";
		file << "@" << passiveValue << "#\n";
		for (auto i = modifierList.begin(); i != modifierList.end(); i++)
		{
			file << "@" << std::to_string((*i)->getCost()) << "#\n";
		}
		file.close();
	}
}

void playerSave::newGame(std::string filename)
{
	saveName = filename; 
	money = 0;
	clickValue = 1; 
	passiveValue = 0;
	pencil.setCost(25);
	scissors.setCost(50);
	coffee.setCost(100);
	thief.setCost(75);
	stock.setCost(150);
	manager.setCost(300);

	std::string path = "saves\\saveFile_";
	path.append(filename);
	path.append(".txt");
	std::ofstream file(path);
	if (std::filesystem::is_empty(std::filesystem::path{ path }) == false)
	{
		file.clear();
	}
	file << "@" << money << "#\n";
	file << "@" << clickValue << "#\n";
	file << "@" << passiveValue << "#\n";
	for (auto i = modifierList.begin(); i != modifierList.end(); i++)
	{
		file << "@" << std::to_string((*i)->getCost()) << "#\n";
	}
	file.close();
}