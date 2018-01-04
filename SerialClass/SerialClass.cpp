/*
 * SerialClass.cpp
 */
 
 // Autor: Rafael Del Lama


#define ARDUINO_WAIT_TIME 2000

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include "SerialClass.h"

/** Construtor padrão
*/
Serial::Serial(){
	
}
/** Construtor
*Recebe o nome da porta e tenta abrir uma conexão.
*/
Serial::Serial(const char *portName) 
{
	//Status conexão
    this->connected = false;
	this->dcbPortaSerialparams = {0};
	this->timeouts = {0};
	this->PortaSerial = CreateFile(portName,
	GENERIC_READ|GENERIC_WRITE,     //para leitura e escrita
	  	0,							//outra abertura não será permitida
	   	NULL,						//atributo de seguranca(null)padrão
	    OPEN_EXISTING, 				//criação ou abertura
		FILE_ATTRIBUTE_NORMAL, 		//ouverlapped
		NULL );
	
this->dcbPortaSerialparams.DCBlength = sizeof(this->dcbPortaSerialparams); 
	if (GetCommState(this->PortaSerial, &this->dcbPortaSerialparams) == 0)
    {
        fprintf(stderr, "Error de estado de dispositivo\n");
        CloseHandle(this->PortaSerial);        
    }
     
    this->dcbPortaSerialparams.BaudRate = CBR_9600;		   //velocidade
    this->dcbPortaSerialparams.ByteSize = 8;			   //tamanho do dado
    this->dcbPortaSerialparams.StopBits = ONESTOPBIT;	   //bits de parada
    this->dcbPortaSerialparams.Parity =  NOPARITY;		   //paridde
    if(SetCommState(this->PortaSerial, &this->dcbPortaSerialparams) == 0)
    {
        fprintf(stderr, "Parametro de dispositivo errado\n");
        CloseHandle(this->PortaSerial);        
    }
    else
    	this->connected = true;
    this->timeouts.ReadIntervalTimeout = 50;
    this->timeouts.ReadTotalTimeoutConstant = 50;
    this->timeouts.ReadTotalTimeoutMultiplier = 10;
    this->timeouts.WriteTotalTimeoutConstant = 50;
    this->timeouts.WriteTotalTimeoutMultiplier = 10;
    if(SetCommTimeouts(this->PortaSerial, &this->timeouts) == 0)
    {
        fprintf(stderr, "timeout configurado errado\n");
        CloseHandle(this->PortaSerial);
    }
	Sleep(2000); //Sleep de 2s para esperar o arduino estar pronto para receber msg  
}//Serial

/** Destrutor
* Se tiver uma conexão estabelecida, fecha a conexão
*/
Serial::~Serial()
{
	Close();
}// ~Serial

/* Fechar a serial
*
*/
void Serial::Close()
{
	fprintf(stderr, "\nFechando porta serial...");
	if(this->connected)
    {
        //We're no longer connected
        this->connected = false;
        //Close the serial handler
     	if (CloseHandle(this->PortaSerial) == 0)
    	{
        	fprintf(stderr, "Error\n");        
    	}
    	fprintf(stderr, "OK\n");
    }
}//Close

/** 
* Le dados através da conexão
*/
void Serial::ReadData(char *bytes)
{
	bool boolean = true;
	int i = 0;
	
	while (PortaSerial != INVALID_HANDLE_VALUE && boolean){
		DWORD bytes_lidos;
	    if (!ReadFile(this->PortaSerial,		//identificador da porta serial
					this->bytes_para_receber,	//buffer, local temporário onde os dados lidos serão armazenados 
					1,					        //tamanho do buffer
					&bytes_lidos,		        //ponteiro onde armazenará a quantidade exata de bytes lidos
					NULL))				        //ponteiro para overlapped
		{
			fprintf(stderr, "Erro\n");
			CloseHandle(this->PortaSerial);		
		} 
		else 
		{
			if (bytes_lidos > 0){
				if(bytes_para_receber[0] == '\n')
					boolean = false;
			
				bytes[i] =  bytes_para_receber[0];
				i++;
			}
		}
	}
}//ReadData

/** 
* Envia dados através da conexão
* buffer contém os dados a serem enviador
*/
void Serial::WriteData(const char *buffer)
{
	int m;
	m = strlen(buffer);
		
	for (int i = 0 ; i != m ; i++)
	{
	    bytes_pra_envio[i] = buffer[i];
	}
   int tamanho = m;

	DWORD bytes_written, total_bytes_written = 0;

    if(!WriteFile(this->PortaSerial,		//identificador da porta serial
				  this->bytes_pra_envio,	//buffer onde será depositado para serem enviados a porta serial
				  tamanho,					//tamanho do buffer de dados
				  &bytes_written,	        //ponteiro onde armazena a quantidade exata de bytes escritos
				  NULL))				    //ponteiro para overlapped
    {
        fprintf(stderr, "Error\n");
        CloseHandle(this->PortaSerial);        
    }   
   
}

/** 
* Retorna o status da conexão
*/
bool Serial::IsConnected()
{
    return this->connected;
}

int Serial::calcFinessArduino(int *indiv, int tam) 
{
	char *s = new char[tam+1];
	int sum = 0;
	for(int i = 0; i < tam; i++){
		s[i] = indiv[i] + 48;
		sum += indiv[i];
	}
	
	WriteData(s);
    
   	char bytes[5];
	ReadData(bytes);
	
	if(sum != atoi(bytes))
		cout << "Errou: " << sum << " " << atoi(bytes) << endl;
	//Sleep(500);

	return atoi(bytes);	
}


