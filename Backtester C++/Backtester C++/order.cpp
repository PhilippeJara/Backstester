#pragma once
#include "order.h"
#include "stockStream.h"


order::order(stockStream* papr, int tpe, double poe,std::string tme, int sze)
{
	if (tpe == 0 || tpe == 1)
	{
		stock = papr;
		type = tpe;
		size = sze;
		time = tme;
		priceOnEntry = poe;
		status = 0;

	}
}
order::order(stockStream* papr, int tpe, double poe, std::string tme, int sze, double sl) 
{
	if (type == 0 || type == 1) 
	{
		stock = papr;
		type = tpe;
		size = sze;
		time = tme;
		priceOnEntry = poe;
		stopLoss = sl;
		status = 0;
	}
}

//get
int order::getType() 
{
	return type;
}
double order::getPriceOnEntry() 
{
	return priceOnEntry;
}
double order::getStopLoss()
{
	return stopLoss;
}
int order::getSize()
{
	if (type==1)
	{
		return size;
	}
	else
	{
		return (size * -1);
	}
}
int order::getSizeModule()
{
	return size;
}
std::string order::getTime()
{
	return time;
}
int order::getStatus()
{
	return status;
}
std::string order::getName() 
{
	return "oi";
}
//change
void order::changeStatus(int stat)
{
	status = stat;
}

