#ifndef PERTURBACAO_H
#define PERTURBACAO_H

using namespace std;

#include <iostream>
#include <vector>
#include <map>
#include "Estruturas.h"
#include "Utilitarios.h"

vector<int> Destruicao (multimap<double, int, greater <int>> & candidatas, vector<Veiculo> & veiculos, int k_max, const vector<double> & demandas, const vector<vector<double>> & matrizDistancias, pair<double, double> & fo);
void Construcao (multimap<double, int, greater <int>> & candidatas, vector<Veiculo> & veiculos, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo, vector<int> & rotasDestruidas);
vector<int> DestruicaoEstocastico (multimap<double, int, greater <int>> & candidatas, vector<Veiculo> & veiculos, int k_max, const vector<double> & demandas, const vector<vector<double>> & matrizDistancias, pair<double, double> & fo);
#endif