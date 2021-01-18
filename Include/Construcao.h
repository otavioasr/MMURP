#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H

using namespace std;

#include <iostream>
#include <vector>
#include <map>
#include "Estruturas.h"
#include "Utilitarios.h"

void GeraSolucaoInicial (multimap<double, int, greater <int>> & candidatas, vector<Veiculo> & veiculos, vector<Deposito> & depositos, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo);
void ClusterizaCandidatas(const vector<double> & demandas, vector<Deposito> & depositos, const vector<vector<double>> & matrizDistancias);
int LocalidadeMaisProxima (vector<int> & rota, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, const vector<int> & candidatas);

#endif