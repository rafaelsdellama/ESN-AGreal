/******************************************************************************\
*								 Fitness:									 *
\******************************************************************************/
#include "defTipo.hpp"
#include "Simulador.hpp"

/******************************************************************************\
*								Calculo Fitness 							 *
\******************************************************************************/
double calcFitness(alelo *indiv, int gen)
{
	
	int Fitness = 0;
	double *mov;
	double *in;
	Simulador *simulador = new Simulador(200,120);

	//Pesos do repositório
	esn->setResWeight(indiv); 
	int n = 1800;

	for(int i = 0; i < n; i++){
		in = simulador->readSensor(10);
		
		mov = esn->Execute(in);
		
		//Define qual movimento vai ser executado (movimento correspondete a maior saída)
		int aux = 0;
		for(int i = 1; i < outputSize; i++)
			if(mov[i] > mov[aux])
				aux = i;
		
		if(!simulador->execute(aux, 10))
			break;
					
		if(aux == 3)
			Fitness++;	
	
		delete mov;
		delete in;
	}

	delete simulador;
		
	return Fitness / (double)n;
}

