#include <stdio.h>
#include <stdlib.h>
#include "mutex.h"
#include "threads.h"
#include <unistd.h>

#define NUM_CADEIRAS 5
#define VERMELHO     "\x1b[31m"
#define VERDE   "\x1b[32m"
#define RESET   "\x1b[0m"


int clientes_esperando, iteracoes;


Mutex mutex;

int barbeiro(int id) {
    while(1) {
        if (clientes_esperando == 0) {
            printf("O barbeiro está dormindo...\n");
	    mutex.WBarbeiro();	
        } else {
            clientes_esperando--;
            mutex.CCliente();  
            printf("O barbeiro está cortando o cabelo de um cliente. Clientes esperando: %d\n", clientes_esperando);     
            //cortando o cabelo
            sleep(3);    
                    
        }
     
    }
    return 0;
    
}


int cliente(int id) {
         
    if (clientes_esperando < NUM_CADEIRAS) {
    	printf("Cliente %d entrou na barbearia. Clientes esperando: %d\n", id, clientes_esperando);   
	clientes_esperando++;
        mutex.WCliente(id);  
        printf(VERDE "Cliente %d cortando o cabelo." RESET "\n", id);      
	 
	 
    } else {
        printf(VERMELHO "A barbearia está cheia. Cliente %d foi embora." RESET "\n", id);
        return -10;
    }
 
    return id;
}

int main() {
    Thread * clientes[NUM_CLIENTES];
    Thread * barb;
    Thread * wake;
    mutex.init();
    clientes_esperando = 0;
    int status;  	

    // Inicializa o barbeiro
    barb = new Thread(&barbeiro,0);
    
    // Inicializa os clientes
    for (int i = 0; i < NUM_CLIENTES; i++) {
        clientes[i] = new Thread(&cliente, i);
        sleep(1); // Simula chegada de clientes em intervalos
    }

    // Aguarda o término das threads    
    for (int j = 0; j < NUM_CLIENTES; j++) {
        clientes[j]->join(&status);               
    }
    barb->join(NULL);	
 
    

    return 0;
}
