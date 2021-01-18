#include "../Include/Utilitarios.h"

void AtualizaDemanda (vector<double> & demandas)
{
	//reduz as demandas que são maiores que a capacidade de um mamografo
	for (double & demanda : demandas)
	{
		if (demanda > 5069)
			demanda = fmod(demanda, 5069);
	}
}

bool PosicaoViavel (const int & deposito, const vector<vector<double>> & matrizDistancias, const int & localidadeAnterior, const int & localidade, const int & localidadePosterior)
{
	if (localidadePosterior == -1)
	{
		double distancia = matrizDistancias[ localidadeAnterior ][ localidade ];

		if ( distancia > 500 || localidadeAnterior != deposito && distancia > 180 
		)
		{
			return false;
		}
	}
	else
	{
		double distancia = matrizDistancias[ localidadeAnterior ][ localidade ];
		double distanciaProximo = matrizDistancias[ localidade ][ localidadePosterior ];

		if ( (localidadeAnterior != deposito && (distancia  > 180 || distanciaProximo  > 180) )
		|| (localidadeAnterior == deposito && distanciaProximo > 180)
		|| (localidadePosterior == deposito)
		|| (distancia  > 500 || distanciaProximo > 500)
		)
		{
			return false;
		}
	}

	return true;
}

void InsereLocalidade (int localidade, Veiculo & veiculo, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo, const int posicao)
{
    //se pos tiver o valor default insere no final da rota
	if (posicao == -1 || posicao == veiculo.rota.size()) 
	{
		double distancia = matrizDistancias[ veiculo.rota.back() ][ localidade ];

		/*
		if (veiculo.capacidadeAtual < demandas[localidade] 
		|| distancia > 500
		|| veiculo.rota.back() != veiculo.codDeposito && distancia > 180 
		)
		{
			return;
		}
		*/

		veiculo.rota.push_back (localidade); 
		veiculo.distanciaTotal += distancia;
		fo.second += distancia;

		veiculo.demandaTotal += demandas[localidade];
		fo.first += demandas[localidade];
		veiculo.capacidadeAtual -= demandas[localidade];
	}
	else
	{
		double distancia = matrizDistancias[ veiculo.rota[posicao-1] ][ localidade ];
		double distanciaProximo = matrizDistancias[ localidade ][ veiculo.rota[posicao] ];

		/*
		if (veiculo.capacidadeAtual < demandas[localidade] 
		|| (veiculo.rota[posicao-1] != veiculo.codDeposito && (distancia  > 180 || distanciaProximo  > 180) )
		|| (veiculo.rota[posicao-1] == veiculo.codDeposito && distanciaProximo > 180)
		|| (veiculo.rota[posicao+1] == veiculo.codDeposito)
		|| (distancia  > 500 || distanciaProximo > 500)
		)
		{
			return;
		}
		*/

		double distanciaRemovida = matrizDistancias[ veiculo.rota[posicao-1] ][ veiculo.rota[posicao] ]; 
		double distanciaInserida = ( distancia + distanciaProximo );

		veiculo.distanciaTotal -= distanciaRemovida;
		fo.second -= distanciaRemovida;

		veiculo.demandaTotal += demandas[localidade];
		fo.first += demandas[localidade];
		veiculo.capacidadeAtual -= demandas[localidade];

		veiculo.rota.insert(veiculo.rota.begin() + posicao, localidade);

		veiculo.distanciaTotal += distanciaInserida;
		fo.second += distanciaInserida;
	}
}

void RemoveLocalidade (Veiculo & veiculo, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo, const int posicao)
{
	if (veiculo.rota[posicao] == veiculo.codDeposito)
			return;

	veiculo.demandaTotal -= demandas[ veiculo.rota[posicao] ];
	fo.first -= demandas[ veiculo.rota[posicao] ];
	veiculo.capacidadeAtual += demandas[ veiculo.rota[posicao] ];
		
	//se for o valor default remove no final da rota
	if (posicao == veiculo.rota.size()-1) 
	{
		double distancia = matrizDistancias[  veiculo.rota[posicao -1] ][  veiculo.rota[posicao] ];
		veiculo.distanciaTotal -= distancia;
		fo.second -= distancia;

		veiculo.rota.pop_back();
	}
	else
	{
		double distancia = matrizDistancias[ veiculo.rota[posicao-1] ][ veiculo.rota[posicao] ];
		double distanciaProximo = matrizDistancias[ veiculo.rota[posicao] ][ veiculo.rota[posicao+1] ];
		
		double distanciaRemovida = (distancia + distanciaProximo); 
		double distanciaInserida = matrizDistancias[ veiculo.rota[posicao-1] ][ veiculo.rota[posicao+1] ];

		veiculo.distanciaTotal -= distanciaRemovida; 
		fo.second -= distanciaRemovida; 

		veiculo.distanciaTotal += distanciaInserida;
		fo.second += distanciaInserida;

		veiculo.rota.erase(veiculo.rota.begin() + posicao);
	}	

}

bool PodeInserir (Veiculo & veiculo, const int & pos, const int & localidade, pair<double, double> & fo, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas)
{
	if (veiculo.capacidadeAtual < demandas[localidade])
		return false;

	if (localidade == veiculo.codDeposito)
		return false;

	if (pos == veiculo.rota.size())
	{
		int localidadeAnterior = veiculo.rota[pos-1];
		double distanciaAte = matrizDistancias[ localidadeAnterior ][ localidade ];

		if (localidadeAnterior != veiculo.codDeposito && (distanciaAte  > 180) ||
			distanciaAte  > 500)
			return false;

		fo.second += matrizDistancias[ localidadeAnterior ][ localidade ];
	}
	else 
	{
		int localidadeAnterior = veiculo.rota[pos-1];
		int localidadePosterior = veiculo.rota[pos];

		double distanciaAte = matrizDistancias[ localidadeAnterior ][ localidade ];
		double distanciaProximo = matrizDistancias[ localidade ][ localidadePosterior ];

		if (localidadeAnterior != veiculo.codDeposito && (distanciaAte  > 180 || distanciaProximo  > 180) ||
		(localidadeAnterior == veiculo.codDeposito && distanciaProximo > 180) ||
		(distanciaAte  > 500 || distanciaProximo > 500))
				return false;
		
		fo.second -= matrizDistancias[ localidadeAnterior ][ localidadePosterior ]; 
		fo.second += matrizDistancias[ localidadeAnterior ][ localidade ]; 
		fo.second += matrizDistancias[ localidade ][ localidadePosterior ];
	}

	return true;
}

bool PodeInserir2 (Veiculo & veiculo, const int & pos, const int & localidade1, const int & localidade2, pair<double, double> & fo, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas)
{
	if (veiculo.capacidadeAtual < (demandas[localidade1] + demandas[localidade2]))
		return false;

	if (localidade1 == veiculo.codDeposito || localidade2 == veiculo.codDeposito)
		return false;

	if (pos == veiculo.rota.size())
	{
		int localidadeAnterior = veiculo.rota[pos-1];
		double distanciaAte = matrizDistancias[ localidadeAnterior ][ localidade1 ];

		if (localidadeAnterior != veiculo.codDeposito && (distanciaAte  > 180) ||
	    	distanciaAte  > 500 )
				return false;

		fo.second += matrizDistancias[ localidadeAnterior ][ localidade1 ]; 
		fo.second += matrizDistancias[ localidade1 ][ localidade2 ]; 
	}
	else
	{
		int localidadeAnterior = veiculo.rota[pos-1];
		int localidadePosterior = veiculo.rota[pos];

		double distanciaAte = matrizDistancias[ localidadeAnterior ][ localidade1 ];
		double distanciaProximo = matrizDistancias[ localidade2 ][ localidadePosterior ];

		if (localidadeAnterior != veiculo.codDeposito && (distanciaAte  > 180 || distanciaProximo  > 180) ||
	   	   (localidadeAnterior == veiculo.codDeposito && distanciaProximo > 180) ||
	   	   (distanciaAte  > 500 || distanciaProximo > 500))
			return false;

		fo.second -= matrizDistancias[ localidadeAnterior ][ localidadePosterior ]; 
		fo.second += matrizDistancias[ localidadeAnterior ][ localidade1 ]; 
		fo.second += matrizDistancias[ localidade1 ][ localidade2 ]; 
		fo.second += matrizDistancias[ localidade2 ][ localidadePosterior ];
	}
	return true;
}

bool PodeRemover (Veiculo & veiculo, const int & pos, pair<double, double> & fo, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas)
{
	int localidade = veiculo.rota[pos];

	if (localidade == veiculo.codDeposito)
		return false;

	if (pos == veiculo.rota.size()-1)
	{
		int localidadeAnterior = veiculo.rota[pos-1];
		fo.second -= matrizDistancias[ localidadeAnterior ][ localidade ]; 
	}
	else
	{
		cout << "\nRota size: " << veiculo.rota.size();
		cout << "\nPos: " << pos;
		
		int localidadeAnterior = veiculo.rota[pos-1];
		int localidadePosterior = veiculo.rota[pos+1];

		if (matrizDistancias[ localidadeAnterior ][ localidadePosterior ] > 180 && localidadeAnterior != veiculo.codDeposito ||
			matrizDistancias[ localidadeAnterior ][ localidadePosterior ] > 500 )
				return false;

		fo.second -= matrizDistancias[ localidadeAnterior ][ localidade ]; 
		fo.second -= matrizDistancias[ localidade ][ localidadePosterior ]; 
		fo.second += matrizDistancias[ localidadeAnterior ][ localidadePosterior ]; 
	}

	return true;
}

bool PodeRemover2 (Veiculo & veiculo, const int & pos, pair<double, double> & fo, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas)
{
	int localidade1 = veiculo.rota[pos];
	int localidade2 = veiculo.rota[pos+1];

	if (localidade1 == veiculo.codDeposito || localidade2 == veiculo.codDeposito)
		return false;

	if (pos == veiculo.rota.size()-2)
	{
		int localidadeAnterior = veiculo.rota[pos-1];

		fo.second -= matrizDistancias[ localidadeAnterior ][ localidade1 ]; 
		fo.second -= matrizDistancias[ localidade1 ][ localidade2 ]; 
	}
	else
	{
		int localidadeAnterior = veiculo.rota[pos-1];
		int localidadePosterior = veiculo.rota[pos+2]; 

		if (matrizDistancias[ localidadeAnterior ][ localidadePosterior ] > 180 && localidadeAnterior != veiculo.codDeposito ||
			matrizDistancias[ localidadeAnterior ][ localidadePosterior ] > 500)
				return false;

		fo.second -= matrizDistancias[ localidadeAnterior ][ localidade1 ]; 
		fo.second -= matrizDistancias[ localidade1 ][ localidade2 ]; 
		fo.second -= matrizDistancias[ localidade2 ][ localidadePosterior ]; 
		fo.second += matrizDistancias[ localidadeAnterior ][ localidadePosterior ]; 
	}
	return true;
}

void MostraVeiculo (Veiculo & veiculo, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas)
{
    cout << "\n\nveiculo do deposito: " << veiculo.codDeposito;
	//cout << "\ndistancia total: " << veiculo.distanciaTotal;
	cout << "\ndemandaTotal: " << veiculo.demandaTotal;
	cout << "\ncapacidade residual: " << veiculo.capacidadeAtual << endl;
		
	cout << "\nlocalidades: ";
	for ( int i : veiculo.rota) 
		cout << i << " ";

	cout << "\ndistancias: ";
	cout << 0 << " ";
	for ( int i = 0; i < veiculo.rota.size(); i++ ) 
	{
		if (i+1 <= veiculo.rota.size()-1)
			cout << matrizDistancias[ veiculo.rota[i] ][ veiculo.rota[i+1] ] << " ";
	}
		
	cout << "\ndemandas: ";
	for ( int i : veiculo.rota)  
		cout << demandas[ i ] << " ";
}

void GeraPlanilhaResultados (vector<Veiculo> & veiculos, const double & tempo_segundos, pair<double, double> & fo)
{
	double 	dep1Demanda = 0, dep2Demanda = 0;
	double 	dep1Distancia = 0, dep2Distancia = 0;
	int 	dep1Veiculos = 0, dep2Veiculos = 0;
	int 	dep1Localidades = 0, dep2Localidades = 0; 

	for ( Veiculo & veiculo : veiculos )
	{
		if (veiculo.idDeposito == 0)
		{
			if (veiculo.rota.size() > 1)
				dep1Veiculos++;

			dep1Distancia += 0;//veiculo.distanciaTotal;
			dep1Demanda += ( veiculo.capacidadeInicial - veiculo.capacidadeAtual );
			dep1Localidades += veiculo.rota.size()-1;
		}

		if (veiculo.idDeposito == 1)
		{
			if (veiculo.rota.size() > 1)
				dep2Veiculos++;
				
			dep2Distancia += 0;//veiculo.distanciaTotal;
			dep2Demanda += ( veiculo.capacidadeInicial - veiculo.capacidadeAtual );
			dep2Localidades += veiculo.rota.size()-1;
		}
	}

	cout << "\n\n" << (dep1Veiculos) << "\\" << (dep2Veiculos) << " " << dep1Localidades  << "\\" << dep2Localidades << " " << fo.first << " " << setprecision(4) <<  (fo.first/358131)*100  << " " << setprecision(9) << fo.second << " " << tempo_segundos;
	
	string arqui = 	"solucao.csv";
    ofstream myfile(arqui,std::ios_base::app);
    if (myfile.is_open()) {
        myfile << endl << (dep1Veiculos) << "," << (dep2Veiculos) << "," 
	        << dep1Veiculos + dep2Veiculos << "," 
	        	<< dep1Localidades  << "," << dep2Localidades << "," 
	        		<< dep1Localidades + dep2Localidades << "," 
	        			<< dep1Demanda << "," << dep2Demanda << ","
		        			<< fo.first << ","
		        				<< setprecision(9) << dep1Distancia << "," << dep2Distancia << "," 
		        					<< setprecision(9) << fo.second << "," 
		        						<< setprecision(4) << (fo.first/358131)*100 << "," 
		        							<< tempo_segundos;
        myfile.close();
    }
}

void EmbaralhaVetor (vector<int> & vetor)
{
	//unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	//shuffle (vetor.begin(), vetor.end(), default_random_engine(seed));
	srand(time(0));
	random_shuffle ( vetor.begin(), vetor.end());
}

vector<int> GeraVetorPosicoes (const int & posInicial, const int & posfinal)
{
	vector<int> vetor;

	for (int i = posInicial; i <= posfinal; i++)
		vetor.push_back(i);

	return vetor;
}









/*
multimap<double, int, greater <int>>::iterator EncontraPosicaoCandidata (multimap<double, int, greater <int>> & candidatas, const int & codigo, const double & demanda)
{
	multimap<double, int, greater <int>>::iterator it = candidatas.find(demanda);

	while (it->second != codigo && it != candidatas.end())
	{
		it++;
	}

	return it;
}
*/
