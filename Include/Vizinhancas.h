#ifndef VIZINHANCAS_H
#define VIZINHANCAS_H

using namespace std;

#include <iostream>
#include <vector>
#include "Estruturas.h"
#include "Utilitarios.h"

void Realoca1 (int pos1, int pos2, Veiculo & veiculo1, Veiculo & veiculo2, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo);
void Realoca2 (int posRemover, int posInserir, Veiculo & veiculo1, Veiculo & veiculo2, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo);
void Troca1 (int pos1, int pos2, Veiculo & veiculo1, Veiculo & veiculo2, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo);
void Troca2 (int pos1, int pos2, Veiculo & veiculo1, Veiculo & veiculo2, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo);

#endif