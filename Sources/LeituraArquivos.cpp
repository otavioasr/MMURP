#include "../Include/LeituraArquivos.h"

void LeConfiguracoes (const string & nomeArquivo, vector<Deposito> & depositos, vector<Veiculo> & veiculos)
{
    vector<string>	dadosLinha;
	int 			codDeposito, idDeposito, qntVeiculos;
	double  		capacidadeVeiculos;

	ifstream arquivo(nomeArquivo);

	LeProximaLinha(arquivo, dadosLinha);

	while(arquivo)
    {
    	dadosLinha.clear();
    	LeProximaLinha(arquivo, dadosLinha);

    	if (dadosLinha.empty())
    		break;

    	vector<double> dadosConvertidos (dadosLinha.size());
    	transform(dadosLinha.begin(), dadosLinha.end(), dadosConvertidos.begin(), ConverteStringParaDouble);
        
		idDeposito = dadosConvertidos[0];
        codDeposito = dadosConvertidos[1];
        qntVeiculos = dadosConvertidos[2];
        capacidadeVeiculos = dadosConvertidos[3];

		Deposito deposito (codDeposito);
		depositos.push_back (deposito);

		for (int i = 0; i < qntVeiculos; i++)
		{
			Veiculo veiculo ( idDeposito, codDeposito, capacidadeVeiculos);
            veiculos.push_back (veiculo);
		}	
    }

	arquivo.close();
}

void LeDistancias (const string & nomeArquivo, vector<vector<double>> & matrizDistancias)
{
	vector<string>	dadosLinha;

	ifstream arquivo(nomeArquivo);

	LeProximaLinha(arquivo, dadosLinha);

    while(arquivo)
    {
    	dadosLinha.clear();
    	LeProximaLinha(arquivo, dadosLinha);
    	
    	if (dadosLinha.empty())
    		break;

    	dadosLinha.erase (dadosLinha.begin());

    	vector<double> dadosConvertidos (dadosLinha.size());
    	transform(dadosLinha.begin(), dadosLinha.end(), dadosConvertidos.begin(), ConverteStringParaDouble);
        matrizDistancias.push_back(dadosConvertidos);	
    }

	arquivo.close();
}

void LeDemandas (const string & nomeArquivo, vector<double> & demandas)
{
	vector<string>	dadosLinha;

	ifstream arquivo(nomeArquivo);

	LeProximaLinha(arquivo, dadosLinha);

	while(arquivo)
    {
    	dadosLinha.clear();
    	LeProximaLinha(arquivo, dadosLinha);

    	if (dadosLinha.empty())
    		break;

    	demandas.push_back( stod(dadosLinha[1]) );
    }

	arquivo.close();
}

void LeProximaLinha (istream& str, vector<string> & dadosLinha)
{
	string         	linha, celula;

	getline(str, linha);
	stringstream linhaStream(linha); 

	while(getline(linhaStream, celula, ' '))
	{
		if (celula == "")
			return;

		dadosLinha.push_back(celula);
	}
};

double ConverteStringParaDouble (const string& valor)
{
    return stod(valor);
};