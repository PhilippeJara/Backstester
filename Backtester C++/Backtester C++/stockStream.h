#pragma once
#include "instrument.h"
#include <string>

class stockStream
{
public:
	instrument* paper;
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
	stockStream::stockStream(instrument*);
	void stockStream::getNext();
	std::string getName();
};