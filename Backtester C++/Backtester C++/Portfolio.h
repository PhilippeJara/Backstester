#pragma once
#include <string>
#include <vector>


class portfolio 
{
	std::string name;
	double cashBalance;
	std::vector<std::vector<std::string>, double> positions;
	double totalBalance;

public:
	std::string portfolio::getName();
	double portfolio::getCash();
	std::vector<std::vector<std::string>, double> portfolio::getPos();
	double portfolio::getBalance();

};