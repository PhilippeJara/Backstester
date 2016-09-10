#pragma once
#include <string>
#include "Portfolio.h"
#include "instrument.h"

class order 
{
	friend class Portfolio;
	std::string name;
	int type; //1 == mrktBuy 0 == mrktSell
	double priceOnEntry;
	double stopLoss;
	int size;
	std::string time;
	int status; //0 == pending 1 == sent 2 == filled and unnoticed 3 == filled and noticed
public:
	order::order(std::string, int, double,std::string, int);
	order::order(std::string, int, double,std::string, int, double);
	//get
	int order::getType();
	double order::getPriceOnEntry();
	double order::getStopLoss();
	int order::getSize();
	int order::getSizeModule();
	std::string order::getTime();
	int order::getStatus();
	std::string order::getName();
	//change
	void order::changeStatus(int);
	//move
	void order::send();

};
