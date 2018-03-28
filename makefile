CPP      = g++
OBJ      = algGen.o defValor.o estatistica.o fitness.o geracao.o reproducao.o salvArq.o selecao.o util_funcions.o nr_ran.o Randon.o TEsn.o
LINKOBJ  = algGen.o defValor.o estatistica.o fitness.o geracao.o reproducao.o salvArq.o selecao.o util_funcions.o nr_ran.o Randon.o TEsn.o
BIN      = algGen_padrao


.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after


$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN)

algGen.o: algGen.cpp
	$(CPP) -c algGen.cpp -o algGen.o 

defValor.o: defValor.cpp
	$(CPP) -c defValor.cpp -o defValor.o 

estatistica.o: estatistica.cpp
	$(CPP) -c estatistica.cpp -o estatistica.o 

fitness.o: fitness.cpp
	$(CPP) -c fitness.cpp -o fitness.o 

geracao.o: geracao.cpp
	$(CPP) -c geracao.cpp -o geracao.o 

reproducao.o: reproducao.cpp
	$(CPP) -c reproducao.cpp -o reproducao.o 

salvArq.o: salvArq.cpp
	$(CPP) -c salvArq.cpp -o salvArq.o 

selecao.o: selecao.cpp
	$(CPP) -c selecao.cpp -o selecao.o 

util_funcions.o: util_funcions.cpp
	$(CPP) -c util_funcions.cpp -o util_funcions.o 

nr_ran.o: nr_ran.cpp
	$(CPP) -c nr_ran.cpp -o nr_ran.o 

Randon.o: Randon.cpp
	$(CPP) -c Randon.cpp -o Randon.o 

TEsn.o: TEsn.cpp
	$(CPP) -c TEsn.cpp -o TEsn.o 