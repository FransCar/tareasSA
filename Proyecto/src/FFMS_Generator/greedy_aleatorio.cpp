#include "FFMS_Generator.hpp"

using namespace std;

string FFMS_Generator::greedy_probabilista(float e){
	// Caracteres posibles, específicos a las instancias a usar.
	vector<char> alfabeto{'A','C','G','T'}; 

	// Estructuras para generar números aleatorios
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> dis(0.0, 1.0);

	string solucion; // Solución inicialmente vacía
	for(int i = 0; i < M; i++){		//Iteramos por posición desde 0 a M.
		map<char, int> frecuencia;	// Mapa para comparar frecuencia de caracteres.
		// Conteo de frecuencias de caracteres.
		for(string s : omega){
			char c = s.at(i);
			if(frecuencia.find(c) == frecuencia.end()){
				frecuencia[c] = 1;
			}else{
				frecuencia[c] = frecuencia[c] + 1;
			}
		}
		// Búsqueda de caracter menos frecuente.
		char minChar = frecuencia.begin()->first;
		for(auto const& pair : frecuencia){
			if(frecuencia[pair.first] < frecuencia[minChar])
				minChar = pair.first;
		}
		// Se selecciona como siguiente en la solución la opción greedy con probabilidad 1-e.
		// Se selecciona una opción aleatoria con una probabilidad e.
		double p = dis(gen);
		uniform_int_distribution<size_t> r_pick(0,alfabeto.size()-1);
		if(p < e){
			solucion.push_back(alfabeto[r_pick(gen)]);
		}else{
			solucion.push_back(minChar);
		}
	}
	return solucion;
}