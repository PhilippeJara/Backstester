#include <iostream>
#include <string>
#include <vector>
#include "csv.h"
#include "instrument.h"
#include "cmdManager.h"
#include "Portfolio.h"
#include "stockStream.h"

int main()
{
	instrument *f[20]; //instrument *f
	csv csv;
	portfolio portfolio("joao",100000.0);
	int instCount = 0;
	int p = 0;
	std::string in;
	std::cin >> in;
	std::string path = "C:\\Users\\Philippe\\Desktop\\papeis\\dados\\" + in + ".csv";
	f[0] = new instrument;  //f = new instrument [x]
	csv.parseToInstrument(*f[0], in, ',');
	stockStream stock(f[0]);
	
	
	/*portfolio.newOrder(f[0]->getName(), 1, f[0]->getClose(40), f[0]->getDate(40), 300);
	portfolio.sendOrder(0);
	portfolio.checkOrders();
	*/
	
	
	
	
	
	
	/*while (p < 1) {
		std::cin >> in;
		cmd.cmdParse(in, f, instCount);
	}*/
	
	std::cout << "abc";
	
	
	
	
	
	
	return 0;
}