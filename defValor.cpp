/******************************************************************************\
*						 Definicao Valor(inicializacao)						 *
\******************************************************************************/

#include "defTipo.hpp"

/* Definicao da variaveis globais */
populacao popVelha , popNova;		
double *arq_media_fitness, *arq_melhor_fitness; 	// dados para serem gravados
double **arq_melhor_individuo;						// dados para serem gravados
Random *random;
ESN *esn;

// Parametros ESN
int inputSize = 4;
int repSize = 5;
int outputSize = 4;
int n_rec = 3;

// Parametros da simulacao
int nroMaxExec = 1;								// numero de repeticoes do AG
int maxGen = 200;									// numero maximo de geracoes 

// Parametros do AG
double taxaCross = 0.6;								// taxa de crossover
double taxaMut = 1.0/lcrom;							// taxa de mutacao

int tamPop = 100;									// tamanho da pop. 
int lcrom = (repSize + 1) * outputSize;				// tamanho do cromossomo 

bool elitismo = true;								// true: elitismo ; false: sem elitismo
int tamTorneio = 3;									// tamanho do torneio (usado na selecao por torneio)
