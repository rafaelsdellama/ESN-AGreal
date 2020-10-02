//Author Rafael Del Lama
 
//-----------------------------------------	TSimulador.hpp -----------------------------------------//

#ifndef SIMULADOR_HPP
#define SIMULADOR_HPP
#include <cmath>

#define PI 3.14159265

class Simulador 
{
	private:
		int sensor (int dist, int ang, int gen);
		int tamX;								// tamanho do tabladoo eixo x
		int tamY;								// tamanho do tabladoo eixo y
		int posX;								// posição do centro do robô no eixo x
		int posY;								// posição do centro do robô no eixo y
		int ang;								// angulo da frente do robô em relação ao eixo x
		int raio;								// raio do robô
		bool dynamicEnvironment;
		int maxGen;
		
	public:
		Simulador(int tamX, int tamY, bool dynamicEnvironment, int maxGen, int gen);
		Simulador(int tamX, int tamY, int raio, int posX, int posY, int ang, bool dynamicEnvironment, int maxGen);
		~Simulador();
		bool execute(int acao, int dist, int gen);
		double* readSensor(int dist, int gen);
		bool isBase();
		int getPosX();
		int getPosY();
		int getAngle();
		
};// class simulador
#endif // SIMULADOR_HPP
