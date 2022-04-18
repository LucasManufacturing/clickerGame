#include "counter.h"
counter::counter()
{
}

int counter::getCount()
{
	return count;
}
int counter::add()
{
	count++;
	return count;
}
int counter::add(int amount)
{
	count = count + amount;
	return count;
}