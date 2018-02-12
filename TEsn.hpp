//Author Rafael Del Lama 
 
//-----------------------------------------	TEsn.h -----------------------------------------//
#ifndef TESN_HPP
#define TESN_HPP

class ESN
{
	public:
		ESN();
		ESN(int inputSize, int repSize, int outputSize, int n_rec);
		~ESN();
		double* Execute (double *in);
		void setResWeight (double *weight);
		double** getWin ();
		void setWin (double **weight);
		double** getW ();
		void setW (double **weight);
		
	private:
		double FuncAtivacao (double x);
		void weightInput();
		
		int inputSize;
		int repSize;
		int outputSize;
		double **Win;
		double **W;
		double **Wout;
		double *outRep;
		double *recorrence;
};

#endif // TESN_HPP
