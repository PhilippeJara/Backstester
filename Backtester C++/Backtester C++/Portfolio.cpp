#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Portfolio.h"
#include "order.h"

portfolio::portfolio(std::string nme, double TBal)
{
	name = nme;
	totalBalance = TBal;
}

//get

std::string portfolio::getName()
{
	return name;
}
double portfolio::getCash() 
{
	return cashBalance;
}
std::vector<std::pair<std::string, double>> portfolio::getPos() 
{
	return position;
}
double portfolio::getBalance() 
{
	return totalBalance;
}
std::vector<order> portfolio::getOrders() 
{
	return orders;
}
order portfolio::getOrder(int indx) 
{
	return orders[indx];
}

//order
 
int portfolio::newOrder(std::string papr, int tpe, double poe, std::string tme, int sze) 
{
	ordersPending.push_back(order(papr, tpe, poe,tme, sze));
	return ordersPending.size();
}
int portfolio::newOrder(std::string papr, int tpe, double poe, std::string tme, int sze, double sl)
{
	ordersPending.push_back(order(papr, tpe, poe, tme, sze, sl));
	return ordersPending.size();
}
int portfolio::sendOrder(int indx)  //o == order sent // send 1 == order already sent // 2 == order alrady filled
{
	if (ordersPending[indx].getStatus == 0) 
	{
		orders[indx].send();
		return 0;
	}
	else 
	{
		if (orders[indx].getStatus == 1) 
		{
			return 1;
		}
		else 
		{
			return 2;
		}
	}
}
void portfolio::checkOrders()
{
	for (int indx = 0; indx < orders.size(); indx++)
	{
		if (orders[indx].getStatus == 2)
		{
			//verificar se tem marge/grana para a operacao concluir
			orders[indx].changeStatus(3);
			//modificar o portfolio
		}
	}
}
//CONTINUAR AQUI!!!
void portfolio::addFilledOrders(order& ordr) 
{
	if (ordr.getType == 0) //1 == mrktBuy 0 == mrktSell
	{
		cashBalance = cashBalance + (ordr.getPriceOnEntry * ordr.getSize); //encontra ganho com a venda do papel
		position.push_back(std::make_pair(ordr.getName, ordr.getSize)); 
	}
}