#pragma once
#include <string>
#include <vector>
#include "Portfolio.h"
#include "order.h"

portfolio::portfolio(std::string nme, double TBal)
{
	name = nme;
	totalBalance = TBal;
}

//fetch req

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
std::vector<order> portfolio::getOrders() 
{
	return orders;
}

//order
 
void portfolio::newOrder(int tpe, double poe, std::string tme, int sze) 
{
	orders.push_back(order(tpe, poe,tme, sze));
}
void portfolio::newOrder(int tpe, double poe, std::string tme, int sze, double sl)
{
	orders.push_back(order(tpe, poe, tme, sze, sl));
}