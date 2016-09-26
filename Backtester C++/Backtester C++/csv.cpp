#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "csv.h"
#include "instrument.h"


csv::csv()
{
	std::vector<std::string> date(0);
	std::vector<double> open(0);
	std::vector<double> high(0);
	std::vector<double> low(0);
	std::vector<double> close(0);
	std::vector<double> volume(0);
};

int csv::parseToInstrument(instrument& papel,std::string path, char delimiter)
{
	std::ifstream file;
	file.open("C:\\Users\\Philippe\\Desktop\\papeis\\dados\\" + path + ".csv");
	if (!file.is_open())
	{
		std::cout << "Falha abrindo o arquivo" << std::endl;
		return 1;
	}
	else
	{
		std::string burner;
		while (file.good())
		{
			std::getline(file, burner);
			int prev_delim = 0;
			int curr_index = 0;
			int coluna = 0;
			papel.name = path;
			for (std::string::iterator it = burner.begin(); it != burner.end(); it++)
			{
				if (*it == delimiter) 
				{
					//date
					if (coluna == 0)
					{
						papel.date.push_back(burner.substr(0, curr_index));
						prev_delim = curr_index;
					} 
					//open
					if (coluna == 1)
					{
						papel.open.push_back(std::stod(burner.substr(prev_delim + 1, curr_index )));
						prev_delim = curr_index;
					} 
					//high
					if (coluna == 2)
					{
						papel.high.push_back(std::stod(burner.substr(prev_delim + 1, curr_index )));
						prev_delim = curr_index;
					} 
					//low
					if (coluna == 3)
					{
						papel.low.push_back(std::stod(burner.substr(prev_delim + 1, curr_index )));
						prev_delim = curr_index;
					}
					//close
					if (coluna == 4)
					{
						papel.close.push_back(std::stod(burner.substr(prev_delim + 1, curr_index )));
						prev_delim = curr_index;
					} 
					//volume
					if (coluna == 5)
					{
						papel.volume.push_back(std::stod(burner.substr(prev_delim + 1, curr_index )));
						prev_delim = curr_index;
					} 
					coluna++;
				}
				curr_index++;
			}
		}
		return 0;
	}
}

