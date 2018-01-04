	/******************************************************************************\
*								 Geracao							 *
\******************************************************************************/

#include "defTipo.hpp"

void geracao(int gen){

	int j = 0 , pai1, pai2;

	do {
		// Escolha dos Pais
		pai1 = selecao( &popVelha , j);
		pai2 = selecao( &popVelha , j+1); 
		
		// Reproducao
		crossover( popVelha.indiv[pai1].cromossomo , popVelha.indiv[pai2].cromossomo , popNova.indiv[j].cromossomo , popNova.indiv[j+1].cromossomo , j);


		// Filho j
		popNova.indiv[j].fitness = calcFitness( popNova.indiv[j].cromossomo, gen );
		popNova.indiv[j].pai1 = pai1;						// pai 1 do filho j
		popNova.indiv[j].pai2 = pai2;						// pai 2 do filho j
		// Filho j + 1
		popNova.indiv[j+1].fitness = calcFitness( popNova.indiv[j+1].cromossomo, gen );
		popNova.indiv[j+1].pai1 = pai1;						// pai 1 do filho j+1
		popNova.indiv[j+1].pai2 = pai2;						// pai 2 do filho j+1
		
		 j = j + 2;											// incremento do índice do individuo

	} while ( j < tamPop);
}
