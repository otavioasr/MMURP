using namespace std;

#include <iostream>
#include <chrono>
#include "Include/Estruturas.h"
#include "Include/Utilitarios.h"
#include "Include/LeituraArquivos.h"
#include "Include/Construcao.h"

#include "Include/Vizinhancas.h"
#include "Include/BuscaLocal.h"
#include "Include/Perturbacao.h"
#include "Include/Metaheuristicas.h"

int main(int argc, char *argv[])
{
    string                                  nomeArquivoConfiguracoes = argv[1];
    int                                     maxIter = stoi(argv[3]);
	int                                     maxNivel = stoi(argv[5]);
    double                                  tempoSegundos;
    pair<double, double>                    fo;
    vector<Veiculo>                         veiculos;
    vector<Deposito>                        depositos;
    vector<double>                          demandas;
	vector<vector<double>>                  matrizDistancias;
    multimap<double, int, greater <int>>    candidatas;

    //srand(time(NULL));

    LeConfiguracoes (nomeArquivoConfiguracoes, depositos, veiculos);
    LeDistancias ("/home/otavio/Documentos/NOVO_MMURP/Data/DistanciasMG.csv", matrizDistancias);
    LeDemandas ("/home/otavio/Documentos/NOVO_MMURP/Data/DemandasMG.csv", demandas);

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    AtualizaDemanda (demandas); //atualiza demandas maiores que a capacidade de um mamografo

    GeraSolucaoInicial (candidatas, veiculos, depositos, matrizDistancias, demandas, fo); //Gera a solução inicial 

    cout << "\nFO ANTERIOR: first " << fo.first << " second: " << fo.second << endl; 
    ILS (candidatas, veiculos,  matrizDistancias, demandas, fo, maxIter, maxNivel);
    //vector<int> rotasDestruidas = DestruicaoEstocastico (candidatas, veiculos, 5, demandas, matrizDistancias, fo);

    chrono::steady_clock::time_point end = chrono::steady_clock::now();
	tempoSegundos = chrono::duration_cast<chrono::microseconds>(end - begin).count() / 1000000.0;

    //RVND(veiculos, matrizDistancias, demandas, fo);
    
    for (int i = 0; i < veiculos.size(); i++)
    {
        cout << "\n\nVEICULO " << i;
        MostraVeiculo(veiculos[i], matrizDistancias, demandas);
    }
    
    cout << "\nFO: first " << fo.first << " second: " << fo.second << endl;   

    GeraPlanilhaResultados (veiculos, tempoSegundos, fo);
    
    return 0;
}






/*

    for (Veiculo veiculo : veiculos)
    {
        for ( int i = 0; i < veiculo.rota.size(); i++ ) 
        {
            if (i+1 <= veiculo.rota.size()-1)
            {
                distanciaTotal += matrizDistancias[ veiculo.rota[i] ][ veiculo.rota[i+1] ];
            }  
        }
    }
    cout << "\nDISTANCIA TOTAL: " << distanciaTotal << endl;

RVND(veiculos, matrizDistancias, demandas, fo);

    cout << "\n\nCANDIDATAS SIZE: " << candidatas.size() << endl;
    for (multimap<double, int, greater <int>>::iterator it=candidatas.begin(); it!=candidatas.end(); ++it)
        std::cout << (*it).first << " => " << (*it).second << '\n';
    vector<int> rotasDestruidas = Destruicao (candidatas, veiculos, maxNivel, demandas, fo);
    
    cout << "\n\nRotas destruidas: ";
    for (int i: rotasDestruidas)
        cout << i << " ";

    Construcao (candidatas, veiculos, matrizDistancias, demandas, fo, rotasDestruidas);
    for (int i = 0; i < veiculos.size(); i++)
    {
        cout << "\n\nVEICULO " << i;
        MostraVeiculo(veiculos[i], matrizDistancias, demandas);
    }
    
    cout << "\nFO: first " << fo.first << " second: " << fo.second << endl;

    //for (int i = 0; i < 100; i++)
    //    RVND(veiculos, matrizDistancias, demandas, fo);

    cout <<  nomeArquivoConfiguracoes << "\n" << maxIter << "\n" << maxNivel << endl;

    cout << "\nDEPOSITOS: " << endl;

    for (int & deposito : depositos)
    {
        cout << deposito << endl;
    }

    cout << "\nVEICULOS: " << endl;
    
    for (Veiculo & veiculo : veiculos)
    {
        cout << veiculo.codDeposito << endl;
    }


    multimap<double, int> ::iterator it;
    std::cout << "candidatas:\n";
    for (it=candidatas.begin(); it!=candidatas.end(); ++it)
        std::cout << (*it).first << " => " << (*it).second << '\n';

    cout << "\n Candidatas size: " << candidatas.size();


    for (int d: depositos[0].candidatas)
        cout << d << endl;

    cout << "\ncand dep 0: " << depositos[0].candidatas.size();

    for ( Veiculo & veiculo : veiculos ) 
	{
        cout << "\nVEICULO " << veiculo.codDeposito << endl;
		for ( int & cidade : veiculo.rota ) 
			cout << cidade << " ";
		
	}
*/