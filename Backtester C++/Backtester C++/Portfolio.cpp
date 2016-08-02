#pragma once
#include <string>
#include <vector>
#include "Portfolio.h"


std::string portfolio::getName()
{
	return name;
}
double portfolio::getCash() 
{
	return cashBalance;
}
std::vector<std::vector<std::string>, double> portfolio::getPos() 
{
	return positions;
}
double portfolio::getBalance() 
{
	return totalBalance;
}
