#pragma once
#include "order.h"
#include "stockStream.h"


order::order(stockStream* stckstream, int tpe, int sze)
{
	if (tpe == 0 || tpe == 1)
	{
		stock = stckstream;
		type = tpe;
		size = sze;
		time = stckstream -> date;
		priceOnEntry = stckstream -> close;
		status = 0;

	}
}
order::order(stockStream* stckstream, int tpe, int sze, double sl) 
{
	if (type == 0 || type == 1) 
	{
		stock = stckstream;
		type = tpe;
		size = sze;
		time = stckstream-> date;
		priceOnEntry = stckstream -> close;
		stopLoss = sl;
		status = 0;
	}
}

//get
int order::getType() {return type;}
double order::getPriceOnEntry() {return priceOnEntry;}
double order::getStopLoss(){return stopLoss;}
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
int order::getAbsoluteSize(){return size;}
std::string order::getTime(){return time;}
int order::getStatus(){return status;}
std::string order::getName() {return stock->name;}
//change
void order::changeStatus(int stat){status = stat;}

