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
	instrument instStack[20]; //instruments on the stack
	csv csv;
	portfolio portfolio("portfolio" , 100000);
	int instCount = 0;
	int p = 0;
	std::string in;
	std::cin >> in;
	std::string path = "C:\\Users\\Philippe\\Desktop\\papeis\\dados\\" + in + ".csv";
	csv.parseToInstrument(instStack[0], in, ',');
	stockStream stock(&instStack[0]);
	for (int i = 0; i < instStack[0].close.size(); i++)
	{
		//if (i % 5 == 0)
		//{
			portfolio.sendOrder(portfolio.newOrder(&stock, 0, 1000) -1);
			portfolio.sendOrder(portfolio.newOrder(&stock, 1, 1000) - 1);
		//}
		portfolio.checkPendingOrders();
		portfolio.update();
		stock.getNext();
	}
	//*portfolio.newOrder(&stock, 1, 300);
	//portfolio.sendOrder(0);
	//portfolio.checkPendingOrders();
	//portfolio.update();
	//stock.getNext();*/
	
	
	
	
	
	
	/*while (p < 1) {
		std::cin >> in;
		cmd.cmdParse(in, f, instCount);
	}*/
	
	std::cout << stock.date;
	
	
	
	
	
	
	return 0;
}