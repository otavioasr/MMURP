#include "../Include/Perturbacao.h"

vector<int> Destruicao (multimap<double, int, greater <int>> & candidatas, vector<Veiculo> & veiculos, int k_max, const vector<double> & demandas, const vector<vector<double>> & matrizDistancias, pair<double, double> & fo)
{
    multimap<double, int, greater <int>> rotasMaisOciosas;
    vector<int> rotasDestruidas;

    for (int i = 0; i < veiculos.size(); i++)
        rotasMaisOciosas.insert(make_pair(veiculos[i].capacidadeAtual, i));

    //cout << "\nrotas mais ociosas: " << endl;
    //for (auto p : rotasMaisOciosas)
    //    cout << p.second << " - " << p.first << endl;

    multimap<double, int, greater <int>>::iterator it = rotasMaisOciosas.begin();
    cout << "\nkmax: " << k_max << endl;
    while (k_max > 0)
    {
        int idVeiculo = (*it).second;
        fo.first -= ( veiculos[idVeiculo].capacidadeInicial - veiculos[idVeiculo].capacidadeAtual );
        
        for (int i = 1; i < veiculos[idVeiculo].rota.size(); i++)
        {
            int localidade = veiculos[idVeiculo].rota[i];
            fo.second -= matrizDistancias[veiculos[idVeiculo].rota[i-1]][localidade];
            
            if (localidade == veiculos[idVeiculo].codDeposito)
                continue;

            candidatas.insert ( pair<double,int>(demandas[localidade], localidade) ); 
        }

        if (veiculos[idVeiculo].rota.size() >= 2 && veiculos[idVeiculo].rota[1] == veiculos[idVeiculo].codDeposito)
        {
            veiculos[idVeiculo].rota.erase(veiculos[idVeiculo].rota.begin()+2, veiculos[idVeiculo].rota.end());
            veiculos[idVeiculo].capacidadeAtual = veiculos[idVeiculo].capacidadeInicial - demandas[veiculos[idVeiculo].codDeposito];
        }
        else
        {
            veiculos[idVeiculo].rota.erase(veiculos[idVeiculo].rota.begin()+1, veiculos[idVeiculo].rota.end());
            veiculos[idVeiculo].capacidadeAtual = veiculos[idVeiculo].capacidadeInicial;
        }
        
        rotasDestruidas.push_back(idVeiculo);
        k_max--;
        it++;
    }

    return rotasDestruidas;
}

void Construcao (multimap<double, int, greater <int>> & candidatas, vector<Veiculo> & veiculos, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo, vector<int> & rotasDestruidas)
{
    multimap<double, int, greater <int>>::iterator it = candidatas.begin();
    cout << "\nCOONSTRUÇÃO: " << endl;
    while (it!=candidatas.end())
    {

        //cout << "\nCandidata " << (*it).first << " - " << (*it).second << endl;
        //cout << " \ndist: " << matrizDistancias[ 562 ][ (*it).second ] << endl;

        //cout << "\nCandidata" << (*it).second << endl;
        //for (int idVeiculo : rotasDestruidas)
        for (int idVeiculo = 0; idVeiculo < veiculos.size(); idVeiculo++)
        {
            if (veiculos[idVeiculo].capacidadeAtual < (*it).first)
                continue;

            double menorDistancia = 10000000;
            int melhorPos;
            bool encontrou = false;
            for (int i = 0; i <= veiculos[idVeiculo].rota.size(); i++)
            {
                if (i != veiculos[idVeiculo].rota.size() && veiculos[idVeiculo].rota[i] == veiculos[idVeiculo].codDeposito)
                    continue;

                if ( (veiculos[idVeiculo].rota[i-1] != veiculos[idVeiculo].codDeposito && matrizDistancias[ veiculos[idVeiculo].rota[i-1] ][ (*it).second ]  > 180 ) ||
                    matrizDistancias[ veiculos[idVeiculo].rota[i-1] ][ (*it).second ]  > 500 ||
                    (i != veiculos[idVeiculo].rota.size() && matrizDistancias[ (*it).second ][ veiculos[idVeiculo].rota[i] ] > 180) )
                    continue;

                double distanciaAtual = matrizDistancias[ veiculos[idVeiculo].rota[i-1] ][ (*it).second ];
                if (i != veiculos[idVeiculo].rota.size())
                    distanciaAtual += matrizDistancias[ (*it).second ][ veiculos[idVeiculo].rota[i] ];

                if (distanciaAtual < menorDistancia)
                {
                    melhorPos = i;
                    menorDistancia = distanciaAtual;
                    encontrou = true;
                }
            }

            if (encontrou)
            {    
                //cout << "\nmelhor pos: " << melhorPos << " veiculo size: " << veiculos[idVeiculo].rota.size();
                
                fo.first += (*it).first;
                fo.second += menorDistancia;
                veiculos[idVeiculo].capacidadeAtual -= (*it).first;
                
                if (melhorPos != veiculos[idVeiculo].rota.size())
                {
                    fo.second -= matrizDistancias[ veiculos[idVeiculo].rota[melhorPos-1] ][ veiculos[idVeiculo].rota[melhorPos] ];
                    veiculos[idVeiculo].rota.insert(veiculos[idVeiculo].rota.begin()+melhorPos, (*it).second);
                }    
                else
                {
                    veiculos[idVeiculo].rota.push_back((*it).second);
                }

                candidatas.erase(it++);
                it = candidatas.begin();
                MostraVeiculo(veiculos[idVeiculo], matrizDistancias, demandas);
                cout << "\ncandidatas size: " << candidatas.size() << endl;
                break;
            }  
        }
        ++it;
    }
    /*
    cout << "\n\nRotas Construidas::: " << endl;
    for (int v : rotasDestruidas)
    {
        MostraVeiculo(veiculos[v], matrizDistancias, demandas);
    }
    */
}

vector<int> DestruicaoEstocastico (multimap<double, int, greater <int>> & candidatas, vector<Veiculo> & veiculos, int k_max, const vector<double> & demandas, const vector<vector<double>> & matrizDistancias, pair<double, double> & fo)
{
    multimap<double, int, greater <int>> rotasMaisOciosas;
    vector<int> rotasDestruidas;

    for (int i = 0; i < veiculos.size(); i++)
        rotasMaisOciosas.insert(make_pair(veiculos[i].capacidadeAtual, i));

    //cout << "\nrotas mais ociosas: " << endl;
    //for (auto p : rotasMaisOciosas)
    //    cout << p.second << " - " << p.first << endl;

    multimap<double, int, greater <int>>::iterator it = rotasMaisOciosas.begin();
    int kMaxAleatorio = ceil(k_max*0.3);

    cout << "\nkmax aleatorio: " << kMaxAleatorio << endl;


    cout << "\nMAIS OCIOSAS: " << endl;
    for (multimap<double, int, greater <int>>::iterator it2 = rotasMaisOciosas.begin(); it2 != rotasMaisOciosas.end(); ++it2)
    {
        cout << (*it2).second << " ";
    }

    for (int i = 0; i < k_max; i++)
    {
        rotasDestruidas.push_back((*it).second);
        it++;
    }

    EmbaralhaVetor(rotasDestruidas);
    rotasDestruidas.erase(rotasDestruidas.begin()+kMaxAleatorio, rotasDestruidas.end());

    for (int idVeiculo : rotasDestruidas)
    {
        cout << "\nDestruiu: " << idVeiculo << endl;

        fo.first -= ( veiculos[idVeiculo].capacidadeInicial - veiculos[idVeiculo].capacidadeAtual );
        
        for (int i = 1; i < veiculos[idVeiculo].rota.size(); i++)
        {
            int localidade = veiculos[idVeiculo].rota[i];
            fo.second -= matrizDistancias[veiculos[idVeiculo].rota[i-1]][localidade];
            
            if (localidade == veiculos[idVeiculo].codDeposito)
                continue;

            candidatas.insert ( pair<double,int>(demandas[localidade], localidade) ); 
        }

        if (veiculos[idVeiculo].rota.size() >= 2 && veiculos[idVeiculo].rota[1] == veiculos[idVeiculo].codDeposito)
        {
            veiculos[idVeiculo].rota.erase(veiculos[idVeiculo].rota.begin()+2, veiculos[idVeiculo].rota.end());
            veiculos[idVeiculo].capacidadeAtual = veiculos[idVeiculo].capacidadeInicial - demandas[veiculos[idVeiculo].codDeposito];
        }
        else
        {
            veiculos[idVeiculo].rota.erase(veiculos[idVeiculo].rota.begin()+1, veiculos[idVeiculo].rota.end());
            veiculos[idVeiculo].capacidadeAtual = veiculos[idVeiculo].capacidadeInicial;
        }
    }
    return rotasDestruidas;
}
