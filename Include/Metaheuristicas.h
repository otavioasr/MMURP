#ifndef METAHEURISTICAS_H
#define METAHEURISTICAS_H

using namespace std;

#include <iostream>
#include <vector>
#include <map>
#include "Estruturas.h"
#include "BuscaLocal.h"
#include "Perturbacao.h"

void ILS (multimap<double, int, greater <int>> & candidatas, vector<Veiculo> & veiculos, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo, int ILS_max, int kMax);

#endif