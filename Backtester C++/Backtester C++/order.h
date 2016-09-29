#pragma once
#include <string>
#include "Portfolio.h"
#include "instrument.h"
#include "stockStream.h"

class order 
{
public:
	friend class Portfolio;
	stockStream* stock;
	int type; //1 == mrktBuy 0 == mrktSell
	double priceOnEntry;
	double stopLoss;
	int size;
	std::string time;
	int status; //0 == pending 1 == sent 2 == filled and unnoticed 3 == filled and noticed

	order::order(stockStream*, int, int);
	order::order(stockStream*, int, int, double);
	//get
	int order::getType();
	double order::getPriceOnEntry();
	double order::getStopLoss();
	int order::getSize();
	int order::getAbsoluteSize();
	std::string order::getTime();
	int order::getStatus();
	std::string order::getName();
	//change
	void order::changeStatus(int);
};
