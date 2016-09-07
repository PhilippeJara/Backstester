#pragma once
#include <string>
#include <vector>
#include "order.h"

class portfolio 
{
	friend class order;
	std::string name;
	double cashBalance;
	std::vector<std::pair<std::string, double>> position;
	std::vector<order> orders;
	double totalBalance;

public:
	portfolio::portfolio(std::string, double);
	std::string portfolio::getName();
	double portfolio::getCash();
	std::vector<std::pair<std::string, double>> portfolio::getPos();
	std::vector<order> portfolio::getOrders();
	double portfolio::getBalance();
	void portfolio::newOrder(int, double, std::string, int);
	void portfolio::newOrder(int, double,std::string, int, double);
};