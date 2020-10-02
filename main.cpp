#include <iostream>
#include "defTipo.hpp"
#include "Simulador.hpp"

using namespace std;

int main(void) {
	bool dynamicEnvironment = true;
	int maxGen = 10;
	int gen = 0;
	Simulador *simulador = new Simulador(120,200, dynamicEnvironment, maxGen, gen);
	cout << "inicial X " << simulador->getPosX() << endl;
	cout << "inicial Y "  << simulador->getPosY() << endl;
	int nrMov  = 10;
		
	int *movimentos = new int [nrMov]; //definir passo a passo
	int *posicoesX = new int [nrMov];
	int *posicoesY = new int [nrMov];
		
	for(int i = 0; i < nrMov; i++ ) {
			
		movimentos[i] = random_int(0, 3);
			
	}
	
	for(int i = 0; i < nrMov; i++ ) {
			
		simulador->execute(movimentos[i], 10, 0);
		posicoesX[i] = simulador->getPosX();
		posicoesY[i] = simulador->getPosY();
		cout << "movimentos " << movimentos[i] << endl;
		cout << "posicoesX " << posicoesX[i] << endl;
		cout << "posicoesY "  <<posicoesY[i] << endl;
		cout << "getAngle "  << simulador->getAngle() << endl;			
			
	}
	
	
	cout<<"\tFim do programa!"<<endl;
 	
	return 0;
}//main
