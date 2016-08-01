#include <iostream>
#include <string>
#include <vector>
#include "csv.h"
#include "instrument.h"

int main()
{	
	int p = 0;
	std::string inputPath;
	std::string path;
	std::string file;
	instrument fI;
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
		result = f[count] -> getDate(500, 800);
		for (int i = 0; i < 299; i++)
		{
			std::cout << result[i] << std::endl;
		}
		count++;
	}
	return 0;
}