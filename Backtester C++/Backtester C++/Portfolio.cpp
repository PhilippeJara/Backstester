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
	marginBalance = 0;
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
		if (totalBalance > ordersPending[indx].getSize() * ordersPending[indx].getPriceOnEntry() && cashBalance > ordersPending[indx].getSize() * ordersPending[indx].getPriceOnEntry()) //verificar se tem margem/grana para a operacao concluir //TEMPORARIO: se o cashbalance é 0, não pode mais comprar
		{	
			ordersPending[indx].changeStatus(3); // orders[indx].send(); envia a ordem para a exchange 
			return 0;
		}
		else
		{
			ordersPending[indx].changeStatus(4);
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
		if (ordersPending[indx].getStatus() > 0 && ordersPending[indx].getStatus() < 4)
		{
			if (ordersPending[indx].getType() == 1 && totalBalance > ordersPending[indx].getSize() * ordersPending[indx].getPriceOnEntry())  //verificar se tem margem para a operacao concluir 
			{	
				processFilledOrder(ordersPending[indx]);
				return;
			}
			if (ordersPending[indx].getType() == 0 && cashBalance > ordersPending[indx].getAbsoluteSize() * ordersPending[indx].getPriceOnEntry()||
				ordersPending[indx].getType() == 0 && stockValue > ordersPending[indx].getAbsoluteSize() * ordersPending[indx].getPriceOnEntry()) // somente permitir a venda de 100% do valor total do portfolio(MUDAR DEPOIS PARA INCORPORAR MARGEM)
			{
				processFilledOrder(ordersPending[indx]);
				return;
			}
		}
	}
}
void portfolio::processFilledOrder(order& ordr)
{
	bool flag = false;
	if (ordr.getType() == 0) //0 == mrktSell 1 == mrktBuy
	{
		for ( int i = 0; i < positions.size(); i++)
		{
			if (ordr.getName() == positions[i].getPaper()) // procura o nome do papel nas posições "filled"
			{ 
				if (ordr.size + positions[i].size < 0) // verifica se é short
				{
					if ((ordr.size * ordr.priceOnEntry) * -1 > totalBalance) //verifica se tem garantias pra entrar descoberto, verdadeiro quando NÃO tem (100% de margem)
					{
						return; // retorna caso não possa shortear por falta de margem
					}
				}
				positions[i].changePos(ordr.getSize()); // caso já haja operação com o papel e -se for o caso- pode shortear, atualiza a posição de tal operação
			}
			
			//caso seja uma posição nova, será short
			if ((ordr.size * ordr.priceOnEntry) * -1 > totalBalance) //verifica se tem garantias ... cópia
			{
				positions.push_back(position(ordr.stock, ordr.getSize())); //adiciona operação às posições
			}
		}
		
		
		
		//for (int i = 0; i < positions.size(); i++)
		//{
		//	if (ordr.getName() == positions[i].getPaper()) // procura o nome do papel nas posições "filled"
		//	{
		//		positions[i].changePos(ordr.getSize()); // caso já haja operação com o papel, atualiza a posição de tal operação
		//		flag = true;
		//		//ordersPending.erase(ordersPending.begin() + i);
		//		//return;
		//	}
		//}
		//if (flag == false)
		//{
		//	if ((ordr.size * ordr.priceOnEntry) + totalBalance > 0)
		//	{
		//		positions.push_back(position(ordr.stock, ordr.getSize())); //SHORT caso o papel não tenha sido negociado ainda e caso tenha balance alto suficiente, adiciona
		//	}
		//}
	}
	else
	{
		cashBalance = cashBalance - (ordr.getPriceOnEntry() * ordr.getAbsoluteSize()); //contabiliza custo com a compra do papel
		stockValue = stockValue + (ordr.stock->close * ordr.getSize());
		for (int i = 0; i < positions.size(); i++)
		{
			if (ordr.getName() == positions[i].getPaper()) // procura o nome do papel nas posições "filled",caso já haja operação com o papel entra
			{
				positions[i].changePos(ordr.getSize()); // atualiza a posição de tal operação
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
	cashBalance = cashBalance + (ordr.getPriceOnEntry() * ordr.getAbsoluteSize()); //contabiliza ganho com a venda do papel
	stockValue = stockValue + (ordr.getPriceOnEntry() * ordr.getSize());
}
void portfolio::update()
{
	for (int i = 0; i < positions.size(); i++)
	{
		if ((positions[i].size > 0 && positions[i].stopLoss > positions[i].paper->close) || (positions[i].size < 0 && 
																		positions[i].stopLoss < positions[i].paper->close)) //verifica o stoploss de ativos , ****debuga ate o talo****
		{
			positions[i].changePos(-positions[i].size);
		}
		if (positions[i].size < 0 && (positions[i].size * positions[i].paper->close) * -1  >  totalBalance) // verifica se há garantias para manter o short 
		{
			positions[i].changePos(-positions[i].size);
		}
		stockValue = stockValue + (positions[i].paper->delta * positions[i].size); //adiciona o delta ao stockValue
	}
	totalBalance = cashBalance + stockValue; //encontra o balanço final
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