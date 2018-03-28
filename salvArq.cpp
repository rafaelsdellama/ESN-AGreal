/******************************************************************************\
*				  				 Grava dados nos arquivos de saida 							 *
\******************************************************************************/
#include "defTipo.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>
//#include <unistd.h>

using namespace std; 

char nameDir[] = "output";

void arq_saida(int nroExec)
{
//	mkdir(nameDir);
	
	int i;
	FILE *Fit_arq,*Melfit_arq;
	char *nome_p;
	char nome[64];

   nome_p = nome;

	// Media do Fitness da Populacao
	sprintf(nome,"%s/fit_%d.dat",nameDir, nroExec);
	if ((Fit_arq = fopen(nome_p,"at+"))==NULL) {
		cout<<"O arquivo de gravacao dos dados de Media do Fitness nao pode ser aberto "<<endl;
		exit(1);
	}
	for (i = 1; i <= maxGen; i++) 
		fprintf(Fit_arq,"%.3lf\n",arq_media_fitness[i]);

	fclose(Fit_arq);

   // Fitness do Melhor Individuo de Cada Geracao
	sprintf(nome,"%s/mfi_%d.dat",nameDir, nroExec);
	if ((Melfit_arq = fopen(nome_p,"at+"))==NULL) {
		cout<<"O arquivo de gravacao dos dados de Melhor Fitness nao pode ser aberto "<<endl;
		exit(1);
	}
	for (i = 1 ; i <= maxGen; i++) 
		fprintf(Melfit_arq,"%.3lf\n",arq_melhor_fitness[i]);
	
	fclose(Melfit_arq);

	//Melhor Individuo de Cada Geracao
	FILE *arq;
	int gene;

	sprintf(nome,"%s/MelhoresIndividuos_%d.dat", nameDir, nroExec); 
	arq = fopen(nome, "at+");
	
	if(arq != NULL)
	{
		for(i = 1; i <= maxGen ; i++) {
			for(gene = 0; gene < lcrom; gene++)
				fprintf(arq, "%lf ",arq_melhor_individuo[i][gene] ); 
			fprintf(arq, "\n");
		}
		int closeResult = fclose(arq);
		if(closeResult == 0)
			cout << "\nMelhores Individuos salvos com sucesso!" << endl;
		else
			cout << "\nErro ao fechar o arquivo!" << endl;
	}
	else
		cout << "\nErro ao abrir o arquivo!" << endl;
		
		salv_pop(nroExec);
		salv_esn(nroExec);
}
//-----------------------------------------------------------------------/
void salv_pop(int nroExec)
{
	int i, gene;
	FILE *Pop_arq;
	char nome[64];
	
	sprintf(nome,"%s/pop_%d.dat", nameDir, nroExec); 
	Pop_arq = fopen(nome, "wt");
	
	if(Pop_arq != NULL)
	{
		//Salva população
		for(i = 0; i < tamPop; i++){
			for(gene = 0; gene < lcrom ; gene++)
				fprintf(Pop_arq, "%lf ",popVelha.indiv[i].cromossomo[gene]);
			fprintf(Pop_arq, "%lf ",popVelha.indiv[i].fitness);
			fprintf(Pop_arq, "\n");
		}
		fprintf(Pop_arq, "%lf ",popVelha.somaFitness); //soma fitness
		fprintf(Pop_arq, "%lf ",popVelha.maxFitness ); //maior fitness
		fprintf(Pop_arq, "%d ",popVelha.melhorIndividuo ); //melhor individuo
		fprintf(Pop_arq, "%d ",popVelha.melhorIndividuo2 ); //melhor2 individuo
		fprintf(Pop_arq, "%lf ",popVelha.mediaFitness); //media fitness
		

		int closeResult = fclose(Pop_arq);
		if(closeResult == 0)
			cout << "Populacao salva com sucesso!" << endl;
		else
			cout << "\nErro ao fechar o arquivo pop.dat!" << endl;
	}
	else
		cout << "\nErro ao abrir o arquivo pop.dat!" << endl;
	
}

//-----------------------------------------------------------------------/
void salv_esn(int nroExec)
{
	FILE *ESN_arq;
	char nome[64];
	
	sprintf(nome,"%s/esn_%d.dat", nameDir, nroExec); 
	ESN_arq = fopen(nome, "wt");
	
	if(ESN_arq != NULL)
	{
		//Salva pesos camada de entrada - Win
		double **Win = esn->getWin();
		for(int i = 0; i < repSize; i++)
			for(int j = 0; j < inputSize + 1; j++)
				fprintf(ESN_arq, "%lf ",Win[i][j]); 
		
		fprintf(ESN_arq, "\n\n");
		//Salva pesos do reservatório - W
		double **W = esn->getW();
		for(int i = 0; i < repSize; i++)
			for(int j = 0; j < repSize; j++)
				fprintf(ESN_arq, "%lf ",W[i][j]); 
	
		int closeResult = fclose(ESN_arq);
		if(closeResult == 0)
			cout << "ESN salva com sucesso!" << endl;
		else
			cout << "\nErro ao fechar o arquivo esn.dat!" << endl;
	
	}
	else
		cout << "\nErro ao abrir o arquivo esn.dat!" << endl;
}

//-----------------------------------------------------------------------/
void salv_traj(int **pos, int n, int nroExec){
//	mkdir(nameDir);

	FILE *traj_arq;
	char nome[64];

	sprintf(nome,"%s/traj_%d.dat", nameDir, nroExec); 
	traj_arq = fopen(nome, "wt");

	if(traj_arq != NULL)
	{
		for(int i = 0; i < n; i++){
			fprintf(traj_arq, "%d ",pos[0][i]);
			fprintf(traj_arq, "%d\n",pos[1][i]); 
		}
		
		int closeResult = fclose(traj_arq);
		if(closeResult == 0)
			cout << "Traj salvo com sucesso!" << endl;
		else
			cout << "\nErro ao fechar o arquivo traj.dat!" << endl;
	}
	else
		cout << "\nErro ao abrir o arquivo traj.dat!" << endl;
}

//-----------------------------------------------------------------------/
void ler_pop(int nroExec)
{
	FILE *Pop_arq;
	char nome[64];
	sprintf(nome,"%s/pop_%d.dat", nameDir, nroExec);

	if ((Pop_arq = fopen(nome,"r"))==NULL) {
		cout<<"O arquivo de gravacao dos dados da populacao nao pode ser aberto "<<endl;
		exit(1);
	}

	int gene, numIndiv = 0;
	while( numIndiv < tamPop) {
	 	for (gene = 0; gene < lcrom; gene++) {
     		fscanf(Pop_arq,"%lf", &popVelha.indiv[numIndiv].cromossomo[gene]); 		
		}
        fscanf(Pop_arq,"%lf", &popVelha.indiv[numIndiv].fitness);					// Armazena Fitness do Individuo
		numIndiv++;
	}

	fscanf(Pop_arq,"%lf", &popVelha.somaFitness); //soma fitness
	fscanf(Pop_arq,"%lf", &popVelha.maxFitness); //maior fitness
	fscanf(Pop_arq,"%d", &popVelha.melhorIndividuo); //melhor individuo
	fscanf(Pop_arq,"%d", &popVelha.melhorIndividuo2); //melhor2 individuo
	fscanf(Pop_arq,"%lf", &popVelha.mediaFitness); //media fitness

	fclose(Pop_arq);
}

//-----------------------------------------------------------------------/
void ler_esn(int nroExec)
{
	FILE *ESN_arq;
	char nome[64];
	sprintf(nome,"%s/esn_%d.dat", nameDir, nroExec); 
	
	if ((ESN_arq = fopen(nome,"r"))==NULL) {
		cout<<"O arquivo de gravacao dos dados da ESN nao pode ser aberto "<<endl;
		exit(1);
	}
	
	double **W, **Win;
	Win = new double*[repSize];
	W = new double*[repSize];
	
	for(int i = 0; i < repSize; i++){
		Win[i] = new double[inputSize + 1]; // +1 = bias
		W[i] = new double[repSize];
	}
	
	//Ler pesos camada de entrada - Win
	for(int i = 0; i < repSize; i++)
		for(int j = 0; j < inputSize + 1; j++)
			fscanf(ESN_arq,"%lf", &Win[i][j]);
	esn->setWin(Win);
			
	//Ler pesos do reservatório - W
	for(int i = 0; i < repSize; i++)
		for(int j = 0; j < repSize; j++)
			fscanf(ESN_arq,"%lf", &W[i][j]);
	esn->setW(W);
	
	fclose(ESN_arq);
}
//-----------------------------------------------------------------------/
void apaga_arquivos(int nroExec)
{
	char nome[64];
	
	sprintf(nome,"%s/pop_%d.dat", nameDir, nroExec); 
	remove(nome);
	sprintf(nome,"%s/MelhoresIndividuos_%d.dat", nameDir, nroExec); 
	remove(nome);
	sprintf(nome,"%s/fit_%d.dat", nameDir, nroExec); 
	remove(nome);
	sprintf(nome,"%s/mfi_%d.dat", nameDir, nroExec); 
	remove(nome); 
	sprintf(nome,"%s/esn_%d.dat", nameDir, nroExec); 
	remove(nome); 
		sprintf(nome,"%s/traj_%d.dat", nameDir, nroExec); 
	remove(nome); 
	cout << "Arquivos apagados com sucesso!" << endl << endl;
}
