#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define NUM_THREADS 5

int saldo = 1000;
pthread_mutex_t mutex;

void *AtualizaSaldo(void *n) {

    pthread_mutex_lock(&mutex);
    int num = (intptr_t)n; 
    
    int meu_saldo = saldo;
    int novo_saldo = meu_saldo + (num * 100); 

    printf("Sou a Thread %d. Novo saldo: %d\n", num, novo_saldo);
    
    int *saldoptr = malloc(sizeof(int));
    *saldoptr = novo_saldo;
    ptrhread_mutex_unlock(&mutex)
    
    pthread_exit(saldoptr);    
    
}

int main() {
    void *status;
    int resultado = 0;    
    
   
    pthread_t threads[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);
    //Criar as threads 
    for(int i =1; i <=NUM_THREADS; i++){
        pthread_create(&threads[i], NULL, AtualizaSaldo, (void*)(intptr_t)i);
    }

    for(int i=1; i <=NUM_THREADS; i++){
        pthread_join(threads[i], &status);
        int *saldo = (int *)status;
        resultado += *saldo;
        free(status);
    }

    pthread_mutex_destroy(&mutex);
    //Coletar os resultados para somar o saldo final 
    printf("Saldo Final: %d\n", resultado);
    return 0;
}