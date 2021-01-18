#include "../Include/Construcao.h"

void GeraSolucaoInicial (multimap<double, int, greater <int>> & candidatas, vector<Veiculo> & veiculos, vector<Deposito> & depositos, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo)
{
	bool encontrou;
	int iLocalidadeMaisProxima;
	pair<double, double> fo_melhor;

	ClusterizaCandidatas (demandas, depositos, matrizDistancias); //cria as LCs por deposito

	for (Veiculo & veiculo : veiculos) //constroi a rota de cada veiculo
	{	
		while (depositos[veiculo.idDeposito].candidatas.size() > 0) //enquanto houver candidatas na LC do deposito do veiculo
		{
			//seleciona a localidade mais proxima da ultima que foi inserida
			iLocalidadeMaisProxima = LocalidadeMaisProxima(veiculo.rota, matrizDistancias, demandas, depositos[veiculo.idDeposito].candidatas);
			int candidata = depositos[veiculo.idDeposito].candidatas[iLocalidadeMaisProxima]; //pega o cod da localidade mais proxima

			if ( veiculo.capacidadeAtual < demandas[candidata] 
			|| !PosicaoViavel (veiculo.codDeposito, matrizDistancias, veiculo.rota.back(), candidata))
				break;
			
			InsereLocalidade (candidata, veiculo, matrizDistancias, demandas, fo); //tenta inserir na rota do veiculo
			
			//apaga a candidata da lista de candidatas
			depositos[veiculo.idDeposito].candidatas.erase (depositos[veiculo.idDeposito].candidatas.begin()+iLocalidadeMaisProxima);
		}
	}

	//insere as candidatas que não estão na solucao em LC
	for (Deposito & deposito : depositos)
	{
		for (int candidata: deposito.candidatas)
			candidatas.insert ( pair<double,int>(demandas[candidata], candidata) );
	}
}

void ClusterizaCandidatas(const vector<double> & demandas, vector<Deposito> & depositos, const vector<vector<double>> & matrizDistancias)
{
	double distancia, menorDistancia;
	double distanciaMaxima, maiorDistancia;
	Deposito * depositoMaisProximo = &depositos[0];

	distanciaMaxima = 500;
	maiorDistancia = 100000;

    //insere na LC as candidatas com demanda diferente de 0 e a 500km de algum deposito
	//insere na LC de cada deposito a candidata mais próxima
	for (int i = 0; i < demandas.size(); i++)
	{
		if (demandas[i] == 0) continue;

		menorDistancia = maiorDistancia;
		for (Deposito & deposito : depositos)
		{
			distancia = matrizDistancias[deposito.codDeposito][i];

			if (distancia < menorDistancia && distancia < distanciaMaxima)
			{
				depositoMaisProximo = &deposito;
				menorDistancia = distancia;
			}
		}

		if (menorDistancia != maiorDistancia)
		{
			depositoMaisProximo->candidatas.push_back(i);
		}
	}
}

int LocalidadeMaisProxima (vector<int> & rota, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, const vector<int> & candidatas)
{
	double distanciaAtual, menorDistancia = 100000000;
	int iMelhor = 0;

	for (int i = 0; i < candidatas.size(); i++)
	{
		distanciaAtual = matrizDistancias[rota.back()][candidatas[i]];																																													

		if (distanciaAtual < menorDistancia || (distanciaAtual == menorDistancia && demandas[candidatas[i]] > demandas[candidatas[iMelhor]]))
		{
			menorDistancia = distanciaAtual;
			iMelhor = i;
		}
	}

	return iMelhor;
}
