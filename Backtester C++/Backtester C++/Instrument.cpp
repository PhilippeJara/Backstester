#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "instrument.h"

instrument::instrument()
{
	std::string name;
	std::vector<std::string> date(0);
	std::vector<double> open(0);
	std::vector<double> high(0);
	std::vector<double> low(0);
	std::vector<double> close(0);
	std::vector<double> volume(0);
};
instrument::instrument(std::string& nome)
{
	std::string name = nome;
	std::vector<std::string> date(0);
	std::vector<double> open(0);
	std::vector<double> high(0);
	std::vector<double> low(0);
	std::vector<double> close(0);
	std::vector<double> volume(0);
};
std::string instrument::getName() 
{
	return name;
}
std::vector<std::string> instrument::getDate()
{
	return date;
}
std::vector<std::string> instrument::getDate(unsigned int lowerIndex, unsigned int upperIndex)
{
	if (date.size() < upperIndex)
	{
		std::cout << "Erro no vetor delimitado" << std::endl;
	}
	else
	{
		std::vector<std::string> ret(0);
		for (int i = lowerIndex; i < upperIndex; i++)
		{
			ret.push_back(date[i]);
		}
		return ret;
	}
}
std::string instrument::getDate(int index)
{
	return date[index];
}
std::vector<double> instrument::getOpen()
{
	return open;
}
std::vector<double> instrument::getOpen(unsigned int lowerIndex, unsigned int upperIndex)
{
	if (open.size() < upperIndex)
	{
		std::cout << "Erro no vetor delimitado" << std::endl;
	}
	else
	{
		std::vector<double> ret(0);
		for (int i = lowerIndex; i < upperIndex; i++)
		{
			ret.push_back(open[i]);
		}
		return ret;
	}
}
double instrument::getOpen(int index)
{
	return open[index];
}
std::vector<double> instrument::getHigh()
{
	return high;
}
std::vector<double> instrument::getHigh(unsigned int lowerIndex, unsigned int upperIndex)
{
	if (high.size() < upperIndex)
	{
		std::cout << "Erro no vetor delimitado" << std::endl;
	}
	else
	{
		std::vector<double> ret(0);
		for (int i = lowerIndex; i < upperIndex; i++)
		{
			ret.push_back(high[i]);
		}
		return ret;
	}
}
double instrument::getHigh(int index)
{
	return high[index];
}
std::vector<double> instrument::getLow() {
	return low;
}
std::vector<double> instrument::getLow(unsigned int lowerIndex, unsigned int upperIndex)
{
	if (low.size() < upperIndex)
	{
		std::cout << "Erro no vetor delimitado" << std::endl;
	}
	else
	{
		std::vector<double> ret(0);
		for (int i = lowerIndex; i < upperIndex; i++)
		{
			ret.push_back(low[i]);
		}
		return ret;
	}
}
double instrument::getLow(int index)
{
	return low[index];
}
std::vector<double> instrument::getClose() {
	return close;
}
std::vector<double> instrument::getClose(unsigned int lowerIndex, unsigned int upperIndex)
{
	if (close.size() < upperIndex)
	{
		std::cout << "Erro no vetor delimitado" << std::endl;
	}
	else
	{
		std::vector<double> ret(0);
		for (int i = lowerIndex; i < upperIndex; i++)
		{
			ret.push_back(close[i]);
		}
		return ret;
	}
}
double instrument::getClose(int index)
{
	return close[index];
}
std::vector<double> instrument::getVolume() {
	return volume;
}
std::vector<double> instrument::getVolume(unsigned int lowerIndex, unsigned int upperIndex)
{
	if (volume.size() < upperIndex)
	{
		std::cout << "Erro no vetor delimitado" << std::endl;
	}
	else
	{
		std::vector<double> ret(0);
		for (int i = lowerIndex; i < upperIndex; i++)
		{
			ret.push_back(volume[i]);
		}
		return ret;
	}
}
double instrument::getVolume(int index)
{
	return volume[index];
}