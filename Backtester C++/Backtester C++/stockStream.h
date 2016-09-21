#pragma once
#include "instrument.h"
#include <string>

class stockStream
{
	instrument *papr;
	std::string date;
	double open;
	double high;
	double low;
	double close;
	double volume;
	int index;
	 
public:
	stockStream::stockStream(instrument*);
	void stockStream::getNext();
};