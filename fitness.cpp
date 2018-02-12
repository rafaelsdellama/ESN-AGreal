/******************************************************************************\
*								 Fitness:									 *
\******************************************************************************/
#include "defTipo.hpp"
#include "Simulador.hpp"

/******************************************************************************\
*								Calculo Fitness Simulador					 *
\******************************************************************************/
double calcFitnessSimulador(alelo *indiv, int gen)
{
	
	int Fitness = 0;
	double *mov;
	double *in;
	Simulador *simulador = new Simulador(200,120);

	//Pesos do repositório
	esn->setResWeight(indiv); 

	for(int i = 0, j = batterry; i < numMov && j > 0; i++, j--){
		in = simulador->readSensor(10);		
		
		mov = esn->Execute(in);				//Verifica a saída da ESN de acordo com a entrada
		
		//Define qual movimento vai ser executado (movimento correspondete ao neuronio de maior ativação)
		int aux = 0;
		for(int k = 1; k < outputSize; k++)
			if(mov[k] > mov[aux])
				aux = k;
		
		//Se o robô bateu, finaliza a simulação
		if(!simulador->execute(aux, 10)) 
			break;
		
		//Verifica se o robô está na base
		if(simulador->isBase())
			j = batterry;						 //Recarrega a bateria
		else
			if(aux == 3) //mov 3 corresponde a andar para frente	
				Fitness++;	
	
		delete mov;
		delete in;
	}

	delete simulador;
		
	return Fitness / (double)numMov;
}


/******************************************************************************\
*								Calculo Fitness 							 *
\******************************************************************************/
double calcFitness(alelo *indiv, int gen)
{
	double Fitness = 0;	
	for(int i = 0; i < 10; i++)
		Fitness += calcFitnessSimulador(indiv, gen);

	Fitness = Fitness / 10;
	return Fitness;
}
