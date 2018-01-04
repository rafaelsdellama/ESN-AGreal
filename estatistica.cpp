/******************************************************************************\
*								 Estatisticas							 *
\******************************************************************************/

#include "defTipo.hpp"

void estatistica( populacao *pop , int gen)
{	
	int j;

	pop->somaFitness = pop->indiv[0].fitness; 		// soma do fitness da populacao 
	pop->maxFitness = pop->indiv[0].fitness;   		// maximo valor de fitness da populacao 
	pop->melhorIndividuo = 0;						// melhor individuo da populacao
	pop->melhorIndividuo2 = 0;						// segundo melhor individuo da populacao

	for(j = 1; j < tamPop; j++) {
		pop->somaFitness = pop->somaFitness + pop->indiv[j].fitness;
		if (pop->indiv[j].fitness >= pop->maxFitness )	{	
			pop->maxFitness = pop->indiv[j].fitness ; 
			pop->melhorIndividuo2 = pop->melhorIndividuo;
			pop->melhorIndividuo = j;			
		}
	}
	
	pop->mediaFitness = pop->somaFitness / tamPop;

	// Dados para serem salvos
	arq_media_fitness[gen] = pop->mediaFitness;
	arq_melhor_fitness[gen] = pop->maxFitness;
	
	int n = pop->melhorIndividuo;
	for(j = 0; j < lcrom; j++)
		arq_melhor_individuo[gen][j] = pop->indiv[n].cromossomo[j];
}			


