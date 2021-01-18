#include "../Include/Metaheuristicas.h"

void ILS (multimap<double, int, greater <int>> & candidatas, vector<Veiculo> & veiculos, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo, int ILS_max, int kMax)
{
    int iter = 0;
    int nivel = 1;
    int melhor_iter = iter;

    RVND (veiculos, matrizDistancias, demandas, fo);

    while (iter - melhor_iter < ILS_max)
    {
        vector<Veiculo> veiculosCopia = veiculos;
        multimap<double, int, greater <int>> candidatasCopia = candidatas;
        pair<double, double> foCopia = fo;
        iter++;

        vector<int> rotasDestruidas = DestruicaoEstocastico (candidatasCopia, veiculosCopia, nivel, demandas, matrizDistancias, foCopia);
        Construcao (candidatasCopia, veiculosCopia, matrizDistancias, demandas, foCopia, rotasDestruidas);
    
        RVND (veiculosCopia, matrizDistancias, demandas, foCopia);
        
        //cout << "\nIteracoes sem melhora: " << (iter - melhor_iter);
        //cout << "\nFO: first " << foCopia.first << " second: " << foCopia.second;
        if ( foCopia.first > fo.first || ( foCopia.first == fo.first && foCopia.second < fo.second ) )
        {
            melhor_iter = iter;
            nivel = 1;
            veiculos = veiculosCopia;
            candidatas = candidatasCopia;
            fo = foCopia;
            //cout << "\nMELHORA";
        }
        else 
        {  
            if (nivel < kMax)
                nivel++;
        }
    }
}