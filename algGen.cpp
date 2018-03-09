/******************************************************************************\
*								 Algoritmo Genetico							 *
\******************************************************************************/
#include "defTipo.hpp"
#include <cstdio>
#include <cstdlib>
#include <cmath>

/******************************************************************************\
*				  	Impressao na tela							 			 *
\******************************************************************************/
void impressao(populacao *pop , int gen) {
	cout <<"Geracao: "<<gen<<endl;
	cout <<"Individuo com melhor fitness: "<<pop->melhorIndividuo<<endl;
	cout <<"Fitness do melhor Individuo: "<<pop->maxFitness<<endl;
    cout <<"Media do Fitness da geracao: "<<pop->mediaFitness<<endl<<endl<<endl;
}//impressao

/******************************************************************************\
*				  Menu					 			 *
\******************************************************************************/
int menu() {
	int op;
	
	do 
	{
		cout << "\t1 - Continuar de onde parou" << endl;
		cout << "\t0 - Reiniciar\n" << endl;
		cin >> op;
	}while (op != 0 && op != 1 );
	
	return op;
}
/******************************************************************************\
*				  	Inicializacao da populacao					 			 *
\******************************************************************************/
void inicializacao(int nroExec, int op) {
	switch(op)
	{
		case 0 : //Reiniciar
		{
			apaga_arquivos(nroExec);
			int gene, numIndiv = 0;
		
			while( numIndiv < tamPop) {
			 	for (gene = 0; gene < lcrom; gene++) {
		     		popVelha.indiv[numIndiv].cromossomo[gene] = random->nextFloat(-1,1) ; 							
				}
		        popVelha.indiv[numIndiv].fitness = calcFitness( popVelha.indiv[numIndiv].cromossomo, 0);	// Armazena Fitness do Individuo
				numIndiv++;
			}
			estatistica( &popVelha,0);
			break;
		}
		case 1 : //Continuar de onde parou
			cout << "Lendo a populacao salva ...\n" << endl;
			ler_pop(nroExec);
			ler_esn(nroExec);
			break;
	}
	impressao(&popVelha,0);

}
/******************************************************************************\
*				  	Execução Algoritimo Genetico							 			 *
\******************************************************************************/
void algGen (int nroExec, int op) {
	int gen = 0 ; 
	
	inicializacao(nroExec, op);				// procedimento para inicialização das variáveis e da população 
	
	do {
		gen = gen + 1; 				// número de gerações 
		geracao(gen);
		estatistica( &popNova , gen ); 

		individuo *aux;
		aux = popVelha.indiv;
		popVelha = popNova;
		popNova.indiv = aux;
		
		impressao(&popVelha,gen);
	} while ( gen < maxGen );
	calcTrajeto (popVelha.indiv[popVelha.melhorIndividuo].cromossomo, nroExec);		//Calcula e salva a trajetoria do melhor indiv da ultima geração
	arq_saida( nroExec);					// salva dados
}

/******************************************************************************\
*				  	main							 			 *
\******************************************************************************/
int main(void) {

	int nroExec, num_ind;

	arq_media_fitness = new double [maxGen+1];
	arq_melhor_fitness = new double [maxGen+1];
	popVelha.indiv = new individuo [tamPop];
	popNova.indiv = new individuo [tamPop];
	for (num_ind = 0; num_ind < tamPop; num_ind++){
		popVelha.indiv[num_ind].cromossomo = new double [lcrom];
		popNova.indiv[num_ind].cromossomo = new double [lcrom];
	}
	arq_melhor_individuo = aloc_matrixd(maxGen+1,lcrom);	
		
	// Execucao	
	cout<<"***** Algoritmo Genetico *****"<<endl;
	int op = menu();
	
	for(nroExec = 0; nroExec < nroMaxExec; nroExec++) {	
		// Visualizacao
		cout<<"\tExecucao: "<<nroExec<<endl<<endl;
		random = new Random(1,nroExec+1);					// semente para gerar os numeros aleatorios
		srand(nroExec+1);									// semente para gerar os numeros aleatorios
		esn = new ESN(inputSize, repSize, outputSize, n_rec);
		algGen(nroExec, op);
		
		delete esn;
		delete random;								// chama a execucao do AG para uma semente aleatoria
	}//for

	// Desalocacao de Memoria
	delete [] arq_media_fitness;
	delete [] arq_melhor_fitness;
	for (num_ind=0; num_ind<tamPop; num_ind++){	
		delete [] popVelha.indiv[num_ind].cromossomo;
		delete [] popNova.indiv[num_ind].cromossomo;
	}
	delete [] popVelha.indiv;
	delete [] popNova.indiv;
	desaloc_matrixd(arq_melhor_individuo,maxGen+1);

	/* Visualizacao */
	cout<<"\tFim do programa!"<<endl;

	system("pause");
 	
	return 0;
}//main

