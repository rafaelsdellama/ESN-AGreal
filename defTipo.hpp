/******************************************************************************\
*								 Definicoes							 *
\******************************************************************************/
#ifndef DEFTIPO_HPP
#define DEFTIPO_HPP

#include "Randon.hpp"
#include "TEsn.hpp"


/* Definicao dos tipos de dados */
typedef double alelo; 						// tipo de dado que os alelos podem assumir 
typedef struct estrutura_individuo {
			alelo *cromossomo;				// cromossomo
			double fitness;					// funcao de avaliacao	
			int pai1 , pai2 ;				// indice dos pais 	
} individuo;

typedef struct {
			individuo *indiv;
			double somaFitness;
			double mediaFitness;
			double maxFitness;
			int melhorIndividuo;
			int melhorIndividuo2;			
} populacao;


/* Definicao da variaveis globais */
extern populacao popVelha , popNova;		
extern int nroMaxExec;									// numero de repeticoes do AG
extern int tamPop, lcrom, maxGen;
extern double taxaCross , taxaMut;						// taxas de crossover e mutacao
extern int tamTorneio;									// tamanho do torneio (usado na selecao por torneio)
extern double *arq_media_fitness, *arq_melhor_fitness;  // dados para serem gravados
extern double **arq_melhor_individuo;						// dados para serem gravados
extern bool elitismo;									// true: elitismo ; false: sem elitismo
extern bool imigracao;									// true: imigracao ; false: sem imigracao
extern double taxaMigracao;								// taxa de imigração
extern bool hipermutacao;								// true: hipermutacao ; false: sem hipermutacao
extern int tamCiclo;									// tamanho do ciclo de hipermutação
extern double taxaR;									//porcentagem de acrescimo na taxa de mutação
extern bool cicloHipermutacao;							//determina se acabou de ocorrer um ciclo de hipermutação
extern ESN *esn;
extern Randon *randon;
extern int inputSize, repSize, outputSize; 				//Parametros ESN
extern double spectral_radius_d, con_density; 			//Parametros ESN
extern int numMov, batterry, numSimulacao;				//Parametros Simulação
extern bool dynamicEnvironment;

/*Declaração das funções */
void algGen ( int nroExec, int op);
void inicializacao(int nroExec, int op);
void impressao(populacao *pop , int gen);
double calcFitness(alelo *indiv, int gen);
double *aloc_vectord(int lines);
individuo *aloc_vectorind(int lines);
double **aloc_matrixd(int lines , int collums);
void desaloc_matrixd(double **Matrix , int lines);
int random_int(int L_range, int H_range);
double random_dou(void);
void estatistica( populacao *pop , int gen );
int selecao( populacao *pop , int j );
void geracao(int gen);
void crossover(alelo *pai1, alelo *pai2, alelo *filho1 , alelo *filho2 ,  int j );
void arq_saida(int nroExec);
void salv_pop(int nroExec);
void salv_esn(int nroExec);
void ler_pop(int nroExec);
void ler_esn(int nroExec);
void apaga_arquivos(int nroExec);
void imigranteAleatorio();
void calcHipermutacao(int gen);
double calcTrajeto (alelo *indiv, int nroExec, int gen);
void salv_traj(int **pos, int n, int nroExec);

//ESN
double largEig(double **M, int l , int c);

#endif // DEFTIPO_HPP
