#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "instrument.h"

class cmd {
public:
	std::string first;
	std::string second;
	std::string third;

	int cmdParse(std::string& ,instrument**,int&);
};