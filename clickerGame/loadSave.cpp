#include "loadSave.h"

loadSave::loadSave()
{
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

}

returnFrame loadSave::update()
{

}