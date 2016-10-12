#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Portfolio.h"
#include "order.h"
#include "stockStream.h"

portfolio::portfolio(std::string nme, double TBal)
{
	name = nme;
	cashBalance = TBal;
	stockValue = 0;
	totalBalance = TBal;
}

//get

std::string portfolio::getName(){return name;}
double portfolio::getCash() {return cashBalance;}
std::vector<position> portfolio::getPos() {return positions;}
double portfolio::getBalance() {return totalBalance;}
std::vector<order> portfolio::getOrders() {return orders;}
order portfolio::getOrder(int indx) {return orders[indx];}

//order
 
int portfolio::newOrder(stockStream* papr, int tpe, int sze) 
{
	ordersPending.push_back(order(papr, tpe, sze));
	return ordersPending.size();
}
int portfolio::newOrder(stockStream* papr, int tpe, int sze, double sl)
{
	ordersPending.push_back(order(papr, tpe, sze, sl));
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
void portfolio::checkPendingOrders()
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
			if (ordersPending[indx].getType() == 0 && totalBalance > ordersPending[indx].getAbsoluteSize() * ordersPending[indx].getPriceOnEntry()) // somente permitir a venda de 100% do valor total do portfolio(MUDAR DEPOIS PARA INCORPORAR MARGEM)
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
		cashBalance = cashBalance + (ordr.getPriceOnEntry() * ordr.getAbsoluteSize()); //contabiliza ganho com a venda do papel
		stockValue = stockValue - (ordr.stock->close * ordr.getSize());
		for (int i = 0; i < positions.size(); i++)
		{
			if (ordr.getName() == positions[i].getPaper()) // procura o nome do papel nas posições "filled"
			{
				positions[i].changePos(ordr.getSize()); // caso já haja operação com o papel, atualiza a posição de tal operação
				return;
			}
		}
		positions.push_back(position(ordr.stock, ordr.getSize()));  // caso o papel não tenha sido negociado ainda, adiciona
	}
	else
	{
		bool flag = false;
		cashBalance = cashBalance - (ordr.getPriceOnEntry() * ordr.getAbsoluteSize()); //contabiliza custo com a compra do papel
		stockValue = stockValue - (ordr.stock->close * ordr.getSize());
		for (int i = 0; i < positions.size(); i++)
		{
			if (ordr.getName() == positions[i].getPaper()) // procura o nome do papel nas posições "filled"
			{
				positions[i].changePos(ordr.getSize()); // caso já haja operação com o papel, atualiza a posição de tal operação
				flag = true;
			}
		}
		if (flag == false)
		{
			positions.push_back(position(ordr.stock, ordr.getSize()));  // caso o papel não tenha sido negociado ainda, adiciona
		}
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
void portfolio::update()
{
	for (int i = 0; i < positions.size(); i++)
	{
		if ((positions[i].size == 0 && positions[i].stopLoss > positions[i].paper->close) || (positions[i].size == 1 && 
																		positions[i].stopLoss < positions[i].paper->close)) //verifica o stoploss de ativos , ****debuga ate o talo****
		{
			positions[i].changePos(-positions[i].size);
		}
		totalBalance = cashBalance + stockValue + (positions[i].paper->delta * positions[i].size) ; //adiciona o delta ao valor total do portfolio, se ele for negativo subtrai
	}
}




//POSITION CLASS

position::position(stockStream* papr, int sze)
{
	paper = papr;
	size = sze;
}
std::string position::getPaper(){return paper->getName();}
int position::getPos(){return size;}
void position::changePos(int change){size = size + change;}
double position::getMargin(){return margin;}