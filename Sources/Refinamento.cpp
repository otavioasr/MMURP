#include "../Include/Refinamento.h"
#include "../Include/Vizinhancas.h"

bool FirstImprovement (Veiculo & veiculo1, Veiculo & veiculo2, const int vizinhanca, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo)
{
	vector<int>				indicesVeiculo1, indicesVeiculo2;
	pair<double, double>    fo_melhor;

	indicesVeiculo1 = GeraVetorPosicoes (1, veiculo1.rota.size());
	EmbaralhaVetor(indicesVeiculo1);
	
	indicesVeiculo2 = GeraVetorPosicoes (1, veiculo2.rota.size());
	EmbaralhaVetor(indicesVeiculo2);

	for (int& pos1 : indicesVeiculo1)
	{
		for (int& pos2 : indicesVeiculo2)
		{	
			fo_melhor = fo;

			if (vizinhanca == 1)
				Realoca1 (pos1, pos2, veiculo1, veiculo2, matrizDistancias, demandas, fo_melhor);
			else if (vizinhanca == 2)
				Realoca2 (pos1, pos2, veiculo1, veiculo2, matrizDistancias, demandas, fo_melhor);
			else if (vizinhanca == 3)
				Troca1 (pos1, pos2, veiculo1, veiculo2, matrizDistancias, demandas, fo_melhor);
			else if (vizinhanca == 4)
				Troca2 (pos1, pos2, veiculo1, veiculo2, matrizDistancias, demandas, fo_melhor);

			if (fo_melhor.second < fo.second)
			{
				fo = fo_melhor;
				return true;
			}
		}
	}

	return false;
}

void DescidaFirstImprovement (vector<Veiculo> & veiculos, const int vizinhanca, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo)
{
	bool 					melhorou, houve_melhora;
	vector<int>				indices;
    pair<double, double>    fo_melhor;

	//cria vetor de indices aleatorios para cada rota
	indices = GeraVetorPosicoes (0, veiculos.size()-1);
	EmbaralhaVetor(indices);

	for (int i = 0; i < indices.size()-1; i++)
	{
		for (int j = i+1; j < indices.size(); j++)
		{
			do
			{
				melhorou = false;
				fo_melhor = fo;
				FirstImprovement (veiculos[indices[i]], veiculos[indices[j]], vizinhanca, matrizDistancias, demandas, fo_melhor);
				if (fo_melhor.second < fo.second) //se tiver reduzido a distancia total percorrida
				{
					fo = fo_melhor;
					melhorou = true;	
				}
			}
			while(melhorou);
		}	
	}
}

