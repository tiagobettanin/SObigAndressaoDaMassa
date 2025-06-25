#include <stdio.h>
#include <stdlib.h>
#include "mutex.h"
#include "threads.h"
#include <unistd.h>

#define NUM_CADEIRAS 5
#define NUM_CLIENTES 10 // Adicionado para o código compilar
#define VERMELHO     "\x1b[31m"
#define VERDE        "\x1b[32m"
#define RESET        "\x1b[0m"


int clientes_esperando;


Mutex mutex;

// Assinaturas corretas para a classe Thread que você provavelmente está usando
int barbeiro(int id);
int cliente(int id);

// --- Início do seu código ---

int barbeiro(int id) {
    while(1) {
        if (clientes_esperando == 0) {
            printf("O barbeiro está dormindo...\n");
            mutex.WBarbeiro();  // Barbeiro espera por um cliente
        } else {
            clientes_esperando--;
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
        mutex.WCliente(id); // Cliente espera na cadeira pela sua vez
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
    mutex.init();
    clientes_esperando = 0;
    int status;

    // Inicializa o barbeiro
    barb = new Thread(&barbeiro,0);
    
    // Simula a chegada de clientes em intervalos
    for (int i = 0; i < NUM_CLIENTES; i++) {
        sleep(1); 
        clientes[i] = new Thread(&cliente, i + 1);
    }

    // Aguarda o término das threads
    for (int j = 0; j < NUM_CLIENTES; j++) {
        clientes[j]->join(&status);
    }
    barb->join(NULL);

    return 0;
}