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
int repSize = 50;
int outputSize = 4;
int n_rec = 3;  									//Não está sendo utilizado!

// Parametros da simulacao
int nroMaxExec = 25;								// numero de repeticoes do AG
int maxGen = 1000;									// numero maximo de geracoes 

// Parametros do AG
double taxaCross = 0.6;								// taxa de crossover
double taxaMut = 1.0/lcrom;							// taxa de mutacao

int tamPop = 100;									// tamanho da pop. 
int lcrom = (repSize + 1) * outputSize;				// tamanho do cromossomo 

bool elitismo = true;								// true: elitismo ; false: sem elitismo
int tamTorneio = 3;									// tamanho do torneio (usado na selecao por torneio)

//Hipermutação
bool hipermutacao = false;							// true: hipermutacao ; false: sem hipermutacao
int tamCiclo = 10;    //maxGen/100;					// tamanho do ciclo de hipermutação
double taxaR = 3;									//porcentagem de acrescimo na taxa de mutação (1 + taxaR)*tavaMut
bool cicloHipermutacao = false;						//determina se acabou de ocorrer um ciclo de hipermutação - NÃO ALTERAR

//Imigração
bool imigracao = false ;							// true: imigracao ; false: sem imigracao
double taxaMigracao = 0.05;							// taxa de imigrantes


//Parametros Simulação
int numMov = 300; //390
int batterry = 80; // 130
