/*
 * SerialClass.h
 */
 
 // Autor: Rafael Del Lama

#ifndef SERIALCLASS_H
#define SERIALCLASS_H

#include <windows.h>
#include <iostream>
#include <stdio.h>

using namespace std;

class Serial
{
    private:
        HANDLE PortaSerial;
        DCB dcbPortaSerialparams;
        COMMTIMEOUTS timeouts;
        
        bool connected;
        char bytes_para_receber[];
        char bytes_pra_envio[];

    public:
    	Serial();
        Serial(const char *portName);
        ~Serial();
        void Close();
        void ReadData(char *bytes);
        void WriteData(const char *buffer);
        bool IsConnected();
        int calcFinessArduino(int *indiv, int tam);
};
#endif // SERIALCLASS_H

