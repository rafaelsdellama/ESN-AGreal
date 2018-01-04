//Author Rafael Del Lama
 
//-----------------------------------------	TSimulador.hpp -----------------------------------------//

#pragma once
#include <cmath>

#define PI 3.14159265

class Simulador 
{
	private:
		int sensor (int dist, int ang);
		int tamX;								// tamanho do tabladoo eixo x
		int tamY;								// tamanho do tabladoo eixo y
		int posX;								// posição do centro do robô no eixo x
		int posY;								// posição do centro do robô no eixo y
		int ang;								// angulo da frente do robô em relação ao eixo x
		int raio;								// raio do robô
		
	public:
		Simulador(int tamX, int tamY);
		Simulador(int tamX, int tamY, int raio, int posX, int posY, int ang);
		~Simulador();
		void execute(int acao, int dist);
		double* readSensor(int dist);
		
};// class simulador
//-----------------------------------------	TSimulador.cpp -----------------------------------------//

//-----------------	simulador -----------------//
Simulador::Simulador(int tamX, int tamY){
	this->tamX = tamX;
	this->tamY = tamY;
	this->raio = 10;
	this->posX = random_int(raio + 5,tamX- (raio + 5));
	this->posY = random_int(raio + 5,tamY-(raio + 5));
	this->ang = 45*random_int(0,7);
}//construtor

//-----------------	simulador -----------------//
Simulador::Simulador(int tamX, int tamY, int raio, int posX, int posY, int ang){
	this->tamX = tamX;
	this->tamY = tamY;
	this->raio = raio;
	this->posX = posX;
	this->posY = posY;
	this->ang = ang;
}//construtor


//-----------------	~simulador -----------------//
Simulador::~Simulador(){
}//destrutor

//-----------------	execute -----------------//
void Simulador::execute(int acao, int dist){
		/*	
			*Ação
		1 -- vira 45º
		2 -- vira -45º	
		3 -- vira 90º	
		4 -- anda p/ frente 10 cm 
		*/			
		switch (acao) 
		{
			case 0 : 
				/** Bloco Rotacionar 45° **/
				ang = ((int)ang + 45) % 360;
				break;
		
			case 1 :
				/** Bloco Rotacionar -45° **/
				ang = ((int)ang + 315) % 360;
				break;

			case 2 :
				/** Bloco Rotacionar 90° **/
				ang = ((int)ang + 90) % 360;
				break;

			case 3 :
				if(sensor(dist, ang) == 0){
					/** Mover para frente 10cm	 M = 1	**/
					posX = posX + dist * cos(ang * PI / 180.0);
					posY = posY + dist * sin(ang * PI / 180.0);
				}
				break;
		}//switch				
}// execute

//-----------------	readSensor -----------------//
double* Simulador::readSensor(int dist){
	double *sensores = new double[4];
	sensores[0] = sensor(dist, ang - 45);
	sensores[1] = sensor(dist, ang);
	sensores[2] = sensor(dist, ang + 45);
	sensores[3] = 0;
	
	return sensores;
}//readSensor

//-----------------	sensor -----------------//
int Simulador::sensor (int dist, int ang){
	double anguloRad = ang * PI / 180.0;
	int distancia = dist + raio;
		 
	if( posX + distancia*cos(anguloRad) >= tamX || posX + distancia*cos(anguloRad) <= 0 || posY + distancia*sin(anguloRad) >= tamY || posY + distancia*sin(anguloRad) <= 0 )
		return 1;
	return 0;
}//sensor
