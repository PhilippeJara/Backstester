#include <iostream>
#include <string>
#include <vector>
#include "csv.h"
#include "instrument.h"
#include "cmdManager.h"

int main()
{
	instrument *f[20];
	cmd cmd;
	int instCount = 0;
	int p = 0;
	std::string in;
	std::string path = "C:\\Users\\Philippe\\Desktop\\papeis\\dados\\" + in + ".csv";
	
	while (p < 1) {
		std::cin >> in;
		cmd.cmdParse(in, f, instCount);
	}
	
	std::cout << "abc";
	
	
	
	
	
	
	
	
	
	
	
	/*int p = 0;
	std::string inputPath;
	std::string path;
	std::string file;
	instrument *f[20];
	int count = 0;
	while (p < 1)
	{
		std::cin >> inputPath;
		path = "C:\\Users\\Philippe\\Desktop\\papeis\\dados\\" + inputPath + ".csv";
		std::vector<std::string> result;
		csv file;
		f[count] = new instrument();
		f[count] -> name = inputPath;
		file.parseToInstrument(*f[count], path, ',');
		result = f[count] -> getDate();
		for (int i = 0; i < 1000; i++)
		{
			std::cout << result[i] << std::endl;
		}
		count++;
	}*/
	return 0;
}