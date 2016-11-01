#pragma once
#include <string>
#include <vector>
#include "order.h"
#include "stockStream.h"

class position
{
	friend class portfolio;
	friend class order;
	stockStream* paper;
	int size;
	double margin;
	double stopLoss;
	position::position(stockStream*, int);
	std::string position::getPaper();
	int position::getPos();
	void position::changePos(int);
	double position::getMargin();
};

class portfolio 
{
	friend class order;
	std::string name;
	double cashBalance;
	double stockValue;
	double marginBalance;
	double totalBalance;
	std::vector<position> positions;
	std::vector<order> orders; //orders == filed
	std::vector<order> ordersPending; // ordersPending == filled and not noticed/not filled

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
	int portfolio::newOrder(stockStream*, int, int);
	int portfolio::newOrder(stockStream*, int, int, double);
	int portfolio::sendOrder(int);
	void portfolio::checkPendingOrders();
	int portfolio::processFilledOrder(order&);
	//update
	void portfolio::update();
};

