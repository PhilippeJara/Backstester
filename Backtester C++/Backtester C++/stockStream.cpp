#pragma once
#include "stockStream.h"
#include <iostream>
#include <fstream>

stockStream::stockStream(instrument* papr)
{
	paper = papr;
	name = papr-> getName();
	delta = 0;
	date = papr -> getDate(0);
	open = papr -> getOpen(0);
	high = papr -> getHigh(0);
	low = papr -> getLow(0);
	close = papr -> getClose(0);
	volume = papr -> getVolume(0);
	index = 0;
	//encontra e define os dados de custos, margens e outras caracteristicas
	
	{
		std::ifstream file;
		file.open("C:\\Users\\Philippe\\Desktop\\papeis\\dados\\costs.csv");
		if (!file.is_open())
		{
			std::cout << "Falha abrindo o arquivo de custos" << std::endl;
			return;
		}
		else
		{
			std::string burner;
			double fxCost = 0;
			double vrCost = 0;
			//int mrgin;
			bool exflag;
			bool match;
			while (file.good())
			{
				std::getline(file, burner);
				exflag = false;
				match = false;
				int prev_delim = 0;
				int curr_index = 0;
				int coluna = 0;
				
				for (std::string::iterator it = burner.begin(); it != burner.end(); it++)
				{
					if (*it == '-')
					{
						exflag = true;
					}
					if (*it == ' ' && exflag == true) // aloca os valores em 
					{
						//nome da exchange
						if (coluna == 0)
						{
							//fixCost = std::stod(burner.substr(1, curr_index));
							prev_delim = curr_index;
						}
						//custo fixo
						if (coluna == 1)
						{
							fxCost = (std::stod(burner.substr(prev_delim + 1, curr_index)));
							prev_delim = curr_index;
						}
						//custo variável
						if (coluna == 2)
						{
							vrCost = (std::stod(burner.substr(prev_delim + 1, curr_index)));
							prev_delim = curr_index;
						}
						coluna++;
					}
					if (exflag == false) // linhas fora da exchange
					{
						if (*it == ' ') 
						{
							if (coluna == 1 && match == true) 
							{
								margin = std::stod(burner.substr(prev_delim, curr_index));
								return;
							}

							if (papr -> getName() == burner.substr(0,curr_index))
							{									
								fixCost = fxCost;
								varCost = vrCost;
								prev_delim = curr_index;
								match = true;
							}
							coluna++;
						}
					}
						
					curr_index++;
				}
			}
		}
		totalCost = close + fixCost;
		return;
	}
}
void stockStream::getNext()
{
	index++;
	delta = (paper -> getClose(index)) - close; // subtrai o valor do ponto que foi chamado com o valor ainda nao atulizado de close 
	open = paper -> getOpen(index);
	high = paper -> getHigh(index);
	low = paper -> getLow(index);
	close = paper -> getClose(index);
	date = paper -> getDate(index);
	return;
}
std::string stockStream::getName() { return name; }