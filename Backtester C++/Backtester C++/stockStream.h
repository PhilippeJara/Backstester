#pragma once
#include "instrument.h"
#include <string>

class stockStream
{
	instrument *papr;
	std::string name;
	std::string date;
	double open;
	double high;
	double low;
	double close;
	double volume;
	double fixCost;
	double varCost;
	double margin;
	double totalCost;
	int index;
	 
public:
	stockStream::stockStream(instrument*);
	void stockStream::getNext();
};