#pragma once
#include <string>
#include <vector>
#include "order.h"

class position
{
	friend class portfolio;
	friend class order;
	std::string paper;
	int pos;
	position::position(std::string, int);
	std::string position::getPaper();
	int position::getPos();
	void position::changePos(int);
};

class portfolio 
{
	friend class order;
	std::string name;
	double cashBalance;
	std::vector<position> positions;
	std::vector<order> orders; //orders == filed
	std::vector<order> ordersPending; // ordersPending == pending/not filled
	double totalBalance;

public:
	portfolio::portfolio(std::string, double);
	std::string portfolio::getName();
	//get
	double portfolio::getCash();
	std::vector<position> portfolio::getPos();
	std::vector<order> portfolio::getOrders();
	double portfolio::getBalance();
	order portfolio::getOrder(int);
	//orders
	int portfolio::newOrder(std::string, int, double, std::string, int);
	int portfolio::newOrder(std::string, int, double, std::string, int, double);
	int portfolio::sendOrder(int);
	void portfolio::checkOrders();
	void portfolio::processFilledOrder(order&);
};

