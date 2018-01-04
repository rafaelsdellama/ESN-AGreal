//Author Rafael Del Lama 

#include "TEsn.hpp"
#include "defTipo.hpp"
#include <iostream>
#include <cmath>

//-----------------------------------------	TEsn.cpp -----------------------------------------//
/* Construtor
* inputSize é a quantidade de entradas da rede ESN
* repSize é a quantidade de neuronios na camada do repositório
* n_rec é o número de recorrencia
*/

ESN::ESN()
{}

ESN::ESN(int inputSize, int repSize, int outputSize, int n_rec)
{
	this->inputSize = inputSize;
	this->repSize = repSize;
	this->outputSize = outputSize;

	Win = new double*[repSize];
	W = new double*[repSize];
	Wout = new double*[outputSize];
	outRep = new double[repSize];
	recorrence = new double[repSize];
	
	for(int i = 0; i < repSize; i++){
		Win[i] = new double[inputSize + 1]; // +1 = bias
		W[i] = new double[repSize];
		recorrence[i] = 0;
	}
	
	for(int i = 0; i < outputSize; i++){
		Wout[i] = new double[repSize + 1]; // +1 = bias
	}
	
    weightInput();
}//ESN

//-----------------	~ESN -----------------//
ESN::~ESN()
{
	for(int i = 0; i < repSize; i++){
		delete Win[i];
		delete W[i];
	}
	for(int i = 0; i < outputSize; i++)
		delete Wout[i];
		
    delete Win;	
    delete W;
    delete Wout;
    delete outRep;
    delete recorrence;
}//~ESN

//-----------------	weightInput -----------------//
/* 
* Inicializa os pesos da camada de entrada e de recorrencia.
*/
void ESN::weightInput(){
	double min_W = -0.6, max_W = 0.6;
	double con_density = 0.15; 

/* Para finalidades praticas, entretanto, basta ajustar o raio espectral ƒÏ(W) de W a um valor abaixo da unidade para garantir a propriedade de echo
state. E tambem importante que a dinamica dos neuronios do reservatorio seja bastante 3 variada. Para isso e necessario que os neuronios do reservatorio apresentem um padrao de
interconexao esparsa (cerca de 1-20%). - esn*/ 

	for(int i = 0; i < repSize; i++){
		for(int j = 0; j < inputSize + 1; j++)
			Win[i][j] = (max_W-min_W)*random_dou() + min_W; 
        
    	for(int j = 0; j < repSize; j++){
    		if (random_dou() < con_density)
        		W[i][j] = (max_W-min_W)*random_dou() + min_W;
        	else
        		W[i][j] = 0;
        }
	}
	cout << "largEig... ";
	// Scaling weights to spectral_radius_d weights
	double spectral_radius = largEig(W, repSize, repSize);
		cout << " calculado!" << endl;
	// Normalizing W to desired spectral radius (Scaling W to spectral_radius_d (1/spectral_radius) W)
	for (int i = 0; i < repSize; i++)
		for (int j = 0; j < repSize; j++)
				W[i][j] = spectral_radius * W[i][j] / spectral_radius;
		
	std::cout << "Conferir geração pesos da primeira camada e recorrencia!" << std::endl;	
}// weightInput

//-----------------	setResWeight -----------------//
/* 
* weight[] é o vetor de pesos do reservatório para a camada de saída
*/
void ESN::setResWeight (double *weight)
{	
	for(int i = 0; i < outputSize; i++)
		for(int j = 0; j < repSize + 1; j++)
			Wout[i][j] = weight[i*repSize + j];			
			
}//setResWeight

//-----------------	execute -----------------//
/* 
* in[] é o vetor de entrada
* return a saída da rede
*/
double* ESN::Execute (double *in)
{	
	for(int i = 0; i < repSize; i++){
		outRep[i] = Win[i][0];
		for(int j = 1; j < inputSize + 1; j++)
			outRep[i] += Win[i][j] * in[j-1];
		outRep[i] = FuncAtivacao(outRep[i]);
	}
	
	for(int i = 0; i < repSize; i++){
		for(int j = 0; j < repSize; j++)
			outRep[i] += W[i][j] * recorrence[i];
		outRep[i] = FuncAtivacao(outRep[i]);
	}

	//Como outRep e recorrence são ponteiros, precisar ser assim..
	double *aux;
	aux = outRep;
	outRep = recorrence;
	recorrence = outRep;
		
	double *out = new double[outputSize];
	for(int i = 0; i < outputSize; i++){
		out[i] = Wout[i][0];
		for(int j = 1; j < repSize + 1; j++)
			out[i] += Wout[i][j] * outRep[j-1]; 
	}

	return out;
}//Execute

//-----------------	FuncAtivacao -----------------//
/*
* retorna o valor da tangente hiperbolica de x
*/
double ESN::FuncAtivacao (double x)
{
	return ( (exp(x) - exp(-x)) / (exp(x) + exp(-x)));	
}//FuncAtivacao

