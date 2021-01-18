#include "../Include/Vizinhancas.h"

void Realoca1 (int pos1, int pos2, Veiculo & veiculo1, Veiculo & veiculo2, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo)
{
    pair<double, double> fo2 = fo;

	if ( pos1 == 0 || pos1 == veiculo1.rota.size() || pos2 == 0)
    {
        //cout << "\nERRO: POSICAO INVALIDA";
        return;
    }

	int localidade = veiculo1.rota[pos1];

	if (veiculo2.capacidadeAtual < demandas[localidade])
		return;

	if (localidade == veiculo1.codDeposito || veiculo2.rota[pos2] == veiculo2.codDeposito)
		return;

	if ( (veiculo2.rota[pos2-1] != veiculo2.codDeposito && matrizDistancias[ veiculo2.rota[pos2-1] ][ localidade ]  > 180 ) ||
			matrizDistancias[ veiculo2.rota[pos2-1] ][ localidade ]  > 500 ||
			(pos2 != veiculo2.rota.size() && matrizDistancias[ localidade ][ veiculo2.rota[pos2] ] > 180) ||
			(pos1+1 <= veiculo1.rota.size()-1 && matrizDistancias[ veiculo1.rota[pos1-1] ][ veiculo1.rota[pos1+1] ]  > 180) )
		return;

	
	fo2.second -= matrizDistancias[ veiculo1.rota[pos1-1] ][veiculo1.rota[pos1]];

	if (pos1+1 <= veiculo1.rota.size()-1)
		fo2.second -= matrizDistancias[ veiculo1.rota[pos1] ][veiculo1.rota[pos1+1]];
	
	if (pos2 != veiculo2.rota.size())
		fo2.second -= matrizDistancias[ veiculo2.rota[pos2-1] ][veiculo2.rota[pos2]];

	if (pos1+1 <= veiculo1.rota.size()-1)
		fo2.second += matrizDistancias[ veiculo1.rota[pos1-1] ][veiculo1.rota[pos1+1]];
	
	fo2.second += matrizDistancias[ veiculo2.rota[pos2-1] ][localidade];

	if (pos2 != veiculo2.rota.size())
		fo2.second += matrizDistancias[ localidade ][veiculo2.rota[pos2]];
	
	if (fo2.second >= fo.second)
		return;

	fo.second = fo2.second;

	veiculo2.capacidadeAtual -= demandas[localidade];
	veiculo1.capacidadeAtual += demandas[localidade];


	//MostraVeiculo(veiculo1, matrizDistancias, demandas);
	//MostraVeiculo(veiculo2, matrizDistancias, demandas);
	//cout << "\nFO: first " << fo.first << " second: " << fo.second;
	//cout << "\npos1: " << pos1 << " pos2: " << pos2 << " veiculo1 size: " << veiculo1.rota.size() << " veiculo2 size: " << veiculo2.rota.size();
	

	veiculo2.rota.insert(veiculo2.rota.begin() + pos2, localidade);
	veiculo1.rota.erase(veiculo1.rota.begin() + pos1);
}


void Realoca2 (int pos1, int pos2, Veiculo & veiculo1, Veiculo & veiculo2, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo)
{
    pair<double, double> fo2 = fo;

	if ( pos1 == 0 || pos1 >= veiculo1.rota.size()-1 || pos2 == 0 )
    {
        //cout << "\nERRO: POSICAO INVALIDA";
        return;
    }

	int localidade1 = veiculo1.rota[pos1];
	int localidade2 = veiculo1.rota[pos1+1];

	if (veiculo2.capacidadeAtual < (demandas[localidade1] + demandas[localidade2]))
		return;

	if (localidade1 == veiculo1.codDeposito || veiculo2.rota[pos2] == veiculo2.codDeposito)
		return;

	if ( (veiculo2.rota[pos2-1] != veiculo2.codDeposito && matrizDistancias[ veiculo2.rota[pos2-1] ][ localidade1 ]  > 180 ) ||
			matrizDistancias[ veiculo2.rota[pos2-1] ][ localidade1 ]  > 500 ||
			(pos2 != veiculo2.rota.size() && matrizDistancias[ localidade2 ][ veiculo2.rota[pos2] ] > 180) ||
			(pos1+2 <= veiculo1.rota.size()-1 && matrizDistancias[ veiculo1.rota[pos1-1] ][ veiculo1.rota[pos1+2] ]  > 180) )
		return;

	fo2.second -= matrizDistancias[ veiculo1.rota[pos1-1] ][localidade1];

	if (pos1+2 <= veiculo1.rota.size()-1)
		fo2.second -= matrizDistancias[ localidade2 ][veiculo1.rota[pos1+2]];
	
	if (pos2 != veiculo2.rota.size())
		fo2.second -= matrizDistancias[ veiculo2.rota[pos2-1] ][veiculo2.rota[pos2]];

	if (pos1+2 <= veiculo1.rota.size()-1)
		fo2.second += matrizDistancias[ veiculo1.rota[pos1-1] ][veiculo1.rota[pos1+2]];
	
	fo2.second += matrizDistancias[ veiculo2.rota[pos2-1] ][localidade1];

	if (pos2 != veiculo2.rota.size())
		fo2.second += matrizDistancias[ localidade2 ][veiculo2.rota[pos2]];

	if (fo2.second >= fo.second)
		return;

	fo.second = fo2.second;

	veiculo2.capacidadeAtual -= demandas[localidade1];
	veiculo2.capacidadeAtual -= demandas[localidade2];
	veiculo1.capacidadeAtual += demandas[localidade1];
	veiculo1.capacidadeAtual += demandas[localidade2];

	veiculo1.rota.erase(veiculo1.rota.begin() + pos1);
	veiculo1.rota.erase(veiculo1.rota.begin() + pos1);

	veiculo2.rota.insert(veiculo2.rota.begin() + pos2, localidade2);
	veiculo2.rota.insert(veiculo2.rota.begin() + pos2, localidade1);
}

void Troca1 (int pos1, int pos2, Veiculo & veiculo1, Veiculo & veiculo2, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo)
{
	pair<double, double> fo2 = fo;

	if ( pos1 == 0 || pos1 >= veiculo1.rota.size() || pos2 == 0 || pos2 >= veiculo2.rota.size())
    {
        //cout << "\nERRO: POSICAO INVALIDA TROCA1";
		//cout << "\npos1: " << pos1 << " pos2: " << pos2 << " veiculo1 size: " << veiculo1.rota.size() << " veiculo2 size: " << veiculo2.rota.size();
        return;
    }

	int localidade1 = veiculo1.rota[pos1];
	int localidade2 = veiculo2.rota[pos2];

	if ( ((veiculo1.capacidadeAtual + demandas[localidade1]) < demandas[localidade2] ) || ((veiculo2.capacidadeAtual + demandas[localidade2]) < demandas[localidade1]))
		return;

	if (localidade1 == veiculo1.codDeposito || localidade2 == veiculo2.codDeposito)
		return;

	if ( (veiculo1.rota[pos1-1] != veiculo1.codDeposito && matrizDistancias[ veiculo1.rota[pos1-1] ][ localidade2 ]  > 180 ) ||
			matrizDistancias[ veiculo1.rota[pos1-1] ][ localidade2 ] > 500 ||
			(pos1+1 <= veiculo1.rota.size()-1 && matrizDistancias[ localidade2 ][ veiculo1.rota[pos1+1] ]  > 180) )
		return;

	if ( (veiculo2.rota[pos2-1] != veiculo2.codDeposito && matrizDistancias[ veiculo2.rota[pos2-1] ][ localidade1 ]  > 180 ) ||
			matrizDistancias[ veiculo2.rota[pos2-1] ][ localidade1 ]  > 500 ||
			(pos2+1 <= veiculo2.rota.size()-1 && matrizDistancias[ localidade1 ][ veiculo2.rota[pos2+1] ]  > 180) )
		return;

	fo2.second -= matrizDistancias[ veiculo1.rota[pos1-1] ][veiculo1.rota[pos1]];
	if (pos1+1 <= veiculo1.rota.size()-1)
		fo2.second -= matrizDistancias[ veiculo1.rota[pos1] ][veiculo1.rota[pos1+1]];

	fo2.second -= matrizDistancias[ veiculo2.rota[pos2-1] ][veiculo2.rota[pos2]];
	if (pos2+1 <= veiculo2.rota.size()-1)
		fo2.second -= matrizDistancias[ veiculo2.rota[pos2] ][veiculo2.rota[pos2+1]];

	fo2.second += matrizDistancias[ veiculo1.rota[pos1-1] ][localidade2];
	if (pos1+1 <= veiculo1.rota.size()-1)
		fo2.second += matrizDistancias[ localidade2 ][veiculo1.rota[pos1+1]];

	fo2.second += matrizDistancias[ veiculo2.rota[pos2-1] ][localidade1];
	if (pos2+1 <= veiculo2.rota.size()-1)
		fo2.second += matrizDistancias[ localidade1 ][veiculo2.rota[pos2+1]];

	if (fo2.second >= fo.second)
		return;

	fo.second = fo2.second;

	veiculo1.capacidadeAtual += demandas[localidade1];
	veiculo1.capacidadeAtual -= demandas[localidade2];

	veiculo2.capacidadeAtual += demandas[localidade2];
	veiculo2.capacidadeAtual -= demandas[localidade1];

	veiculo1.rota.erase(veiculo1.rota.begin() + pos1);
	veiculo1.rota.insert(veiculo1.rota.begin() + pos1, localidade2);

	veiculo2.rota.erase(veiculo2.rota.begin() + pos2);
	veiculo2.rota.insert(veiculo2.rota.begin() + pos2, localidade1);
}

void Troca2 (int pos1, int pos2, Veiculo & veiculo1, Veiculo & veiculo2, const vector<vector<double>> & matrizDistancias, const vector<double> & demandas, pair<double, double> & fo)
{
	pair<double, double> fo2 = fo;

	if ( pos1 == 0 || pos1 >= veiculo1.rota.size()-1 || pos2 == 0 || pos2 >= veiculo2.rota.size() )
    {
        //cout << "\nERRO: POSICAO INVALIDA TROCA1";
		//cout << "\npos1: " << pos1 << " pos2: " << pos2 << " veiculo1 size: " << veiculo1.rota.size() << " veiculo2 size: " << veiculo2.rota.size();
        return;
    }

	int localidade1 = veiculo1.rota[pos1];
	int localidade1_2 = veiculo1.rota[pos1+1];
	int localidade2 = veiculo2.rota[pos2];

	if ( ((veiculo1.capacidadeAtual + demandas[localidade1] + demandas[localidade1_2]) < demandas[localidade2]) || 
		((veiculo2.capacidadeAtual + demandas[localidade2]) < (demandas[localidade1] + demandas[localidade1_2]) ) )
		return;

	if (localidade1 == veiculo1.codDeposito || localidade2 == veiculo2.codDeposito)
		return;

	if ( (veiculo1.rota[pos1-1] != veiculo1.codDeposito && matrizDistancias[ veiculo1.rota[pos1-1] ][ localidade2 ]  > 180 ) ||
			matrizDistancias[ veiculo1.rota[pos1-1] ][ localidade2 ] > 500 ||
			(pos1+2 <= veiculo1.rota.size()-1 && matrizDistancias[ localidade2 ][ veiculo1.rota[pos1+2] ]  > 180) )
		return;

	if ( (veiculo2.rota[pos2-1] != veiculo2.codDeposito && matrizDistancias[ veiculo2.rota[pos2-1] ][ localidade1 ]  > 180 ) ||
			matrizDistancias[ veiculo2.rota[pos2-1] ][ localidade1 ]  > 500 ||
			(pos2+1 <= veiculo2.rota.size()-1 && matrizDistancias[ localidade1_2 ][ veiculo2.rota[pos2+1] ]  > 180) )
		return;

	fo2.second -= matrizDistancias[ veiculo1.rota[pos1-1] ][localidade1];
	if (pos1+2 <= veiculo1.rota.size()-1)
		fo2.second -= matrizDistancias[localidade1_2][veiculo1.rota[pos1+2]];

	fo2.second -= matrizDistancias[ veiculo2.rota[pos2-1] ][localidade2];
	if (pos2+1 <= veiculo2.rota.size()-1)
		fo2.second -= matrizDistancias[localidade2][veiculo2.rota[pos2+1]];

	fo2.second += matrizDistancias[ veiculo1.rota[pos1-1] ][localidade2];
	if (pos1+2 <= veiculo1.rota.size()-1)
		fo2.second += matrizDistancias[ localidade2 ][veiculo1.rota[pos1+2]];

	fo2.second += matrizDistancias[ veiculo2.rota[pos2-1] ][localidade1];
	if (pos2+1 <= veiculo2.rota.size()-1)
		fo2.second += matrizDistancias[ localidade1_2 ][veiculo2.rota[pos2+1]];

	if (fo2.second >= fo.second)
		return;

	fo.second = fo2.second;

	veiculo1.capacidadeAtual += demandas[localidade1];
	veiculo1.capacidadeAtual += demandas[localidade1_2];
	veiculo1.capacidadeAtual -= demandas[localidade2];

	veiculo2.capacidadeAtual += demandas[localidade2];
	veiculo2.capacidadeAtual -= demandas[localidade1];
	veiculo2.capacidadeAtual -= demandas[localidade1_2];

	veiculo1.rota.erase(veiculo1.rota.begin() + pos1);
	veiculo1.rota.erase(veiculo1.rota.begin() + pos1);
	veiculo1.rota.insert(veiculo1.rota.begin() + pos1, localidade2);

	veiculo2.rota.erase(veiculo2.rota.begin() + pos2);
	veiculo2.rota.insert(veiculo2.rota.begin() + pos2, localidade1_2);
	veiculo2.rota.insert(veiculo2.rota.begin() + pos2, localidade1);
}
