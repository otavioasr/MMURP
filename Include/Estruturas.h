#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

using namespace std;

#include <iostream>
#include <vector>

struct Deposito
{
	int 				codDeposito;
	double 				capacidade;
	vector<int>		    candidatas;

	Deposito (int& _codDeposito) : codDeposito(_codDeposito){}

};

struct Veiculo
{
    int 			    idDeposito, codDeposito;
    double 				capacidadeAtual, capacidadeInicial, distanciaTotal, demandaTotal;
    vector<int> 		rota;

    Veiculo (const int & _idDeposito, const int & _codDeposito, const double & _capacidadeInicial) : idDeposito(_idDeposito), codDeposito(_codDeposito), capacidadeInicial(_capacidadeInicial)
    {
    	rota.push_back (codDeposito);
    	capacidadeAtual = capacidadeInicial;
    }
};

#endif