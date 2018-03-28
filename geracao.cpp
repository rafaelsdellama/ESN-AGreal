	/******************************************************************************\
*								 Geracao							 *
\******************************************************************************/

#include "defTipo.hpp"

void geracao(int gen){

	int j = 0 , pai1, pai2;

	if(hipermutacao && gen % tamCiclo == 0)
		calcHipermutacao(gen);

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
		
	if(imigracao)
		imigranteAleatorio();
}


/******************************************************************************\
*								 Imigrantes Aleatórios						 *
\******************************************************************************/
void imigranteAleatorio()
{
	int gene, individuo = 0;
	if(elitismo)
		individuo = 2;
		
	for(	; individuo < tamPop; individuo++)
		if (random_dou () < taxaMigracao) {	
			for (gene = 0; gene < lcrom; gene++) {
				popNova.indiv[individuo].cromossomo[gene] = randon->nextFloat(-1,1); 							// inteiro aleatorio entre 0 e 1
			}
		}
}

/******************************************************************************\
*								 Hipermutação							 *
\******************************************************************************/
void calcHipermutacao(int gen)
{
	if(cicloHipermutacao) {
		taxaMut = taxaMut / (1 + taxaR);
		cicloHipermutacao = false;
		return;
	}
	
	if(gen % (2*tamCiclo) == 0) { // se já ocorreram 2 ciclos	
		int i, j;
		double ciclo1 = 0, ciclo2 = 0;
		
		for(i = gen - 2*tamCiclo, j = gen - tamCiclo; j < gen; i++, j++) {
			ciclo1 += arq_melhor_fitness[i];
			ciclo2 += arq_melhor_fitness[j];
		}
		
		if(ciclo1 >= ciclo2) {
			taxaMut = taxaMut*(1 + taxaR);
			cicloHipermutacao = true;
		}
	}
}
