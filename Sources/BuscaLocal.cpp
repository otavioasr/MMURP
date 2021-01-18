#include "../Include/BuscaLocal.h"
#include "../Include/Utilitarios.h"
#include "../Include/Refinamento.h"

void RVND (vector<Veiculo> & veiculos, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo)
{	
	pair<double, double> 			melhor_fo;
	bool							melhorou = false;
	vector<int> 					vizinhanca_inicial, vizinhanca;

	vizinhanca_inicial = {1, 2, 3, 4};
	EmbaralhaVetor(vizinhanca_inicial);

    vizinhanca = vizinhanca_inicial; 

	while (!vizinhanca.empty())
	{
		melhor_fo = fo;
		DescidaFirstImprovement(veiculos, vizinhanca[0], matrizDistancias, demandas, melhor_fo);
		
		if ( melhor_fo.second < fo.second )
		{
			vizinhanca = vizinhanca_inicial;
			EmbaralhaVetor(vizinhanca_inicial);
				
			fo = melhor_fo;
			//cout << "	\nMELHOROOOU" << endl;
		}
		else
		{
			vizinhanca.erase(vizinhanca.begin());
		}
	}
}
