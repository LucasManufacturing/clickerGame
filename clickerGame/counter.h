#pragma once
class counter
{
public: 
	counter(); 
	int getCount();
	int add();
	int add(int amount);
private:
	int count = 0; 
};

