#ifndef BUSCALOCAL_H
#define BUSCALOCAL_H

using namespace std;

#include <iostream>
#include <vector>
#include "Estruturas.h"

void RVND (vector<Veiculo> & veiculos, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo);

#endif