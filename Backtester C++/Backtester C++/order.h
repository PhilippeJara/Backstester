#pragma once
#include <string>
#include "Portfolio.h"
class order 
{
	friend class Portfolio;
	int type; //1 == mrktBuy 0 == mrktSell
	double priceOnEntry;
	double stopLoss;
	int size;
	std::string time;
	int status; //0 == pending 1 == filled
public:
	order::order(int, double,std::string, int);
	order::order(int, double,std::string, int, double);
};
