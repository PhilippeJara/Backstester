#pragma once
#include <string>
#include <vector>
#include "instrument.h"

class instrument;

class csv
{
public:
	csv::csv();
	int csv::parseToInstrument(instrument&, std::string, char);
};