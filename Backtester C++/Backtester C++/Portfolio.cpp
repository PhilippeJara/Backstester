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
std::vector<std::pair<std::string, double>> portfolio::getPos() 
{
	return position;
}
double portfolio::getBalance() 
{
	return totalBalance;
}
