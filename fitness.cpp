/******************************************************************************\
*								 Fitness:									 *
\******************************************************************************/
#include "defTipo.hpp"
#include "Simulador.hpp"
#include <iostream>

/******************************************************************************\
*								Calculo Fitness 							 *
\******************************************************************************/
double calcFitness(alelo *indiv, int gen)
{
	int Fitness = 0;
	double *mov;
	double *in;
	Simulador *simulador = new Simulador(200,120);
	esn = new ESN(inputSize, repSize, outputSize, n_rec);

	//Pesos do repositório
	esn->setResWeight(indiv); 
	int n = 1000;
	for(int i = 0; i < n; i++){
		in = simulador->readSensor(10);
		
		mov = esn->Execute(in);
		
		//Define qual movimento vai ser executado (movimento correspondete a maior saída)
		int aux = 0;
		for(int i = 1; i < outputSize; i++)
			if(mov[i] > mov[aux])
				aux = i;
		
		simulador->execute(aux, 10);
		
		if(aux == 3)
			Fitness++;	
	}
	delete esn;
	delete simulador;
		
	return Fitness / (double)n;
}

