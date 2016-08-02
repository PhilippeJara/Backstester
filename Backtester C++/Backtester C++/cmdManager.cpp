#pragma once
#include "cmdManager.h"
#include <vector>


int cmd::cmdParse(std::string& input, instrument** instruments,int& instrumentCount) 
{
	//Definindo qual a ordem dos comandos
	first = "";
	second = "";
	third = "";
	int delCount = 0;
	int lastDel = 0;
	int lastIndex = 0;
	
	for (std::string::iterator it = input.begin(); it != input.end(); it++)
	{
		if (*it == '.') 
		{
			if (delCount == 0)
			{
				first = input.substr(0, lastIndex);
			}
			if (delCount == 1)
			{
				second = input.substr(lastDel, lastIndex);
			}
			
			lastDel = lastIndex;
			delCount++;
		}
		lastIndex++;
	}
	if (second != "")
	{ 
		third = input.substr(lastDel +1, input.size()); 
	}
	else if(first !="")
	{
		second = input.substr(lastDel +1, input.size());
	}
	
	//usando os comandos

	//instruments
	
	//criar instrumentos

	if (delCount == 0) 
	{
		 if(instrumentCount <= 20)
			{
				csv csv;
				instruments[instrumentCount] = new instrument(input);
				csv.parseToInstrument(*instruments[instrumentCount], "C:\\Users\\Philippe\\Desktop\\papeis\\dados\\" + input + ".csv", ',');
				instrumentCount++;
				return 0;

			}
		}
	
	
	/*if (first == "inst") 
	{
		for (int i = 0; i != instruments.size - 1;i++) 
		{
			if (second == instruments[i].getName()) 
			{
				std::cout << "deu certo";
			}
		}
	}*/
	
	
	return 0;
}