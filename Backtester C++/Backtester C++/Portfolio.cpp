#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Portfolio.h"
#include "order.h"

portfolio::portfolio(std::string nme, double TBal)
{
	name = nme;
	cashBalance = TBal;
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
std::vector<position> portfolio::getPos() 
{
	return positions;
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
int portfolio::sendOrder(int indx)  //o == order sucessfully sent // 1 == order already sent // 2 == order alrady filled // 9 == error
{
	if (ordersPending[indx].getStatus() == 0) 
	{
		if (totalBalance > ordersPending[indx].getSize() * ordersPending[indx].getPriceOnEntry()) //verificar se tem margem/grana para a operacao concluir 
		{	
			ordersPending[indx].changeStatus(3); // orders[indx].send(); envia a ordem para a exchange 
			return 0;
		}
	}
	else
	{
		if (orders[indx].getStatus() == 1) 
		{
			return 1;
		}
		else 
		{
			ordersPending[indx].changeStatus(3);
			return 2;
		}
	}
	return 9;
}
void portfolio::checkOrders()
{
	for (int indx = 0; indx < ordersPending.size(); indx++)
	{
		if (ordersPending[indx].getStatus() > 0)
		{
			if (ordersPending[indx].getType() == 1 && totalBalance > ordersPending[indx].getSize() * ordersPending[indx].getPriceOnEntry())  //verificar se tem margem para a operacao concluir 
			{	
				processFilledOrder(ordersPending[indx]);
				return;
			}
			if (ordersPending[indx].getType() == 0) // se for ordem de venda efetuar (MUDAR DEPOIS PARA INCORPORAR MARGEM)
			{
				processFilledOrder(ordersPending[indx]);
				return;
			}
		}
	}
}
void portfolio::processFilledOrder(order& ordr)
{
	if (ordr.getType() == 0) //1 == mrktBuy 0 == mrktSell
	{
		cashBalance = cashBalance + (ordr.getPriceOnEntry() * ordr.getSizeModule()); //encontra ganho com a venda do papel
		for (int i = 0; i < positions.size(); i++)
		{
			if (ordr.getName() == positions[i].getPaper()) // procura o nome do papel nas posições "filled"
			{
				positions[i].changePos(ordr.getSize()); // caso já haja operação com o papel, atualiza a posição de tal operação
				return;
			}
		}
		positions.push_back(position(ordr.getName(), ordr.getSize()));  // caso o papel não tenha sido negociado ainda, adiciona
	}
	else
	{
		cashBalance = cashBalance - (ordr.getPriceOnEntry() * ordr.getSizeModule()); //encontra custo com a compra do papel
		for (int i = 0; i < positions.size(); i++)
		{
			if (ordr.getName() == positions[i].getPaper()) // procura o nome do papel nas posições "filled"
			{
				positions[i].changePos(ordr.getSize()); // caso já haja operação com o papel, atualiza a posição de tal operação
				return;
			}
		}
		
		positions.push_back(position(ordr.getName(), ordr.getSize()));  // caso o papel não tenha sido negociado ainda, adiciona
	}
	for (int i = 0; i < ordersPending.size(); i++) // procura aonde em ordersPending o papel está, move o papel para orders e o deleta de ordersPending
	{
		if (ordersPending[i].getStatus() == 3)
		{
			orders.push_back(ordr);
			ordersPending.erase(ordersPending.begin() + i);
		}
	}
}





//POSITION CLASS

position::position(std::string papr, int size)
{
	paper = papr;
	pos = size;
}
std::string position::getPaper()
{
	return paper;
}
int position::getPos()
{
	return pos;
}
void position::changePos(int change)
{
	pos = pos + change;
}