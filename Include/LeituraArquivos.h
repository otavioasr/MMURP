#ifndef LEITURA_ARQUIVOS_H
#define LEITURA_ARQUIVOS_H

using namespace std;

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include "Estruturas.h"

void LeConfiguracoes (const string & nomeArquivo, vector<Deposito> & depositos, vector<Veiculo> & veiculos);
void LeDistancias (const string & nomeArquivo, vector<vector<double>> & matrizDistancias);
void LeDemandas (const string & nomeArquivo, vector<double> & demandas);
void LeProximaLinha (istream& str, vector<string> & dadosLinha);
double ConverteStringParaDouble (const string& valor);

#endif