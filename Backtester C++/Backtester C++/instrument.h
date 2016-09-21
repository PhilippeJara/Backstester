#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "csv.h"

class csv;

class instrument 
{
public:
	std::string name;
	std::vector<std::string> date;
	std::vector<double> open;
	std::vector<double> high;
	std::vector<double> low;
	std::vector<double> close;
	std::vector<double> volume;


//public:
	instrument::instrument();
	instrument::instrument(std::string&);
	
	friend class csv;
	
	std::string instrument::getName();


	std::vector<std::string> instrument::getDate();
	std::vector<std::string> instrument::getDate(unsigned int, unsigned int);
	std::string instrument::getDate(int);

	std::vector<double> instrument::getOpen();
	std::vector<double> instrument::getOpen(unsigned int, unsigned int);
	double instrument::getOpen(int);

	std::vector<double> instrument::getHigh();
	std::vector<double> instrument::getHigh(unsigned int, unsigned int);
	double instrument::getHigh(int);

	std::vector<double> instrument::getLow();
	std::vector<double> instrument::getLow(unsigned int, unsigned int);
	double instrument::getLow(int);

	std::vector<double> instrument::getClose();
	std::vector<double> instrument::getClose(unsigned int, unsigned int);
	double instrument::getClose(int);

	std::vector<double> instrument::getVolume();
	std::vector<double> instrument::getVolume(unsigned int, unsigned int);
	double instrument::getVolume(int);
};