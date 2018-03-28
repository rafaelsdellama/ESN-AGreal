/******************************************************************************\
*								 Selecao									 *
\******************************************************************************/

#include "defTipo.hpp"


/******************************************************************************\
*								Elitismo											 *
\*******************************************************************************/
int selecaoElitismo(populacao *pop , int j)
{
	int individuoEscolhido;

	if (j == 0){
		individuoEscolhido = pop->melhorIndividuo;
	}
	else {
		individuoEscolhido = pop->melhorIndividuo2;
	}
	return individuoEscolhido;
}


/******************************************************************************\
*								Selecao por torneio							 *
\*******************************************************************************/
int selecaoTorneio(populacao *pop)
{
	int i, individuo_rand, individuo_esc;
	
	individuo_esc=random_int(0, (tamPop-1) );
	for (i=1;i<tamTorneio;i++){
		individuo_rand=random_int(0, (tamPop-1) );
		if ( pop->indiv[individuo_rand].fitness > pop->indiv[individuo_esc].fitness  )
			individuo_esc=individuo_rand;
	}
		
	return individuo_esc;
}

/******************************************************************************\
*								Selecao											 *
\*******************************************************************************/
int selecao( populacao *pop , int j ) 
{
	int individuoEscolhido;
	
	if ( elitismo == 1 && j < 2 ){
		individuoEscolhido = selecaoElitismo( pop , j );
	}
	else {
		individuoEscolhido = selecaoTorneio( pop );
	}
	
 	return individuoEscolhido;
}



