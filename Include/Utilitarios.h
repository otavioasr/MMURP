#ifndef UTILITARIOS_H
#define UTILITARIOS_H

using namespace std;

#include <iostream>
#include <vector>
#include <math.h>
#include <map>
#include <fstream> 
#include <iomanip>
#include <algorithm>
#include <chrono>
#include <random> 
#include "Estruturas.h"

void AtualizaDemanda (vector<double> & demandas);
bool PosicaoViavel (const int & deposito, const vector<vector<double>> & matrizDistancias, const int & localidadeAnterior, const int & localidade, const int & localidadePosterior = -1);
void InsereLocalidade (int localidade, Veiculo & veiculo, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo, const int posicao = -1);
void RemoveLocalidade (Veiculo & veiculo, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo, const int posicao = -1);
void MostraVeiculo (Veiculo & veiculo, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas);
void GeraPlanilhaResultados (vector<Veiculo> & veiculos, const double & tempo_segundos, pair<double, double> & fo);
void EmbaralhaVetor (vector<int> & vetor);
vector<int> GeraVetorPosicoes (const int & posInicial, const int & posfinal);

bool PodeInserir (Veiculo & veiculo, const int & pos, const int & localidade, pair<double, double> & fo, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas);
bool PodeRemover (Veiculo & veiculo, const int & pos, pair<double, double> & fo, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas);
bool PodeInserir2 (Veiculo & veiculo, const int & pos, const int & localidade1, const int & localidade2, pair<double, double> & fo, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas);
bool PodeRemover2 (Veiculo & veiculo, const int & pos, pair<double, double> & fo, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas);

#endif