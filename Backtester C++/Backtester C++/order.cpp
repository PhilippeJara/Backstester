#include "order.h"


order::order(int tpe, double poe,std::string tme, int sze)
{
	if (tpe == 0 || tpe == 1)
	{
		type = tpe;
		size = sze;
		time = tme;
		priceOnEntry = poe;

	}
}
order::order(int tpe, double poe, std::string tme, int sze, double sl) 
{
	if (type == 0 || type == 1) 
	{
		type = tpe;
		size = sze;
		time = tme;
		priceOnEntry = poe;
		stopLoss = sl;
	}
}
