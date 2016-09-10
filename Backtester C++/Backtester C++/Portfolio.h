#pragma once
#include <string>
#include <vector>
#include "order.h"

class portfolio 
{
	friend class order;
	std::string name;
	double cashBalance;
	std::vector<std::pair<std::string, int>> position;
	std::vector<order> orders; //orders == filed
	std::vector<order> ordersPending; // ordersPending == pending/not filled
	double totalBalance;

public:
	portfolio::portfolio(std::string, double);
	std::string portfolio::getName();
	//get
	double portfolio::getCash();
	std::vector<std::pair<std::string, double>> portfolio::getPos();
	std::vector<order> portfolio::getOrders();
	double portfolio::getBalance();
	order portfolio::getOrder(int);
	//orders
	int portfolio::newOrder(std::string, int, double, std::string, int);
	int portfolio::newOrder(std::string, int, double, std::string, int, double);
	int portfolio::sendOrder(int);
	void portfolio::checkOrders();
	void portfolio::addFilledOrders(order&);
};