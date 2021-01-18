#ifndef REFINAMENTO_H
#define REFINAMENTO_H

using namespace std;

#include "Estruturas.h"
#include "Utilitarios.h"

void DescidaFirstImprovement (vector<Veiculo> & veiculos, const int vizinhanca, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo);
bool FirstImprovement (Veiculo & veiculo1, Veiculo & veiculo2, const int vizinhanca, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo);

#endif