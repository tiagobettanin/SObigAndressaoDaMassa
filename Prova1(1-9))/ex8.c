/*
8) A seguinte informação: "processos pai e filho compartilham código, mas não dados"; é verdadeira? 
Demonstre a sua resposta com um programa - exemplo.
Resposta: Sim essa informação está correta, pois diferentes processos inicialmente não compartilham dados porem utilizando pipe sim eles podem
*/

#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>

int main (void){
    int pik = fork();
    int exemplo= 10;
    
    if(pik>0){
        printf("Sou pai e o valor de exemplo eh %d", exemplo);
        exemplo = exemplo +10;
        printf(" e alterei o valor para %d\n", exemplo);
        wait(NULL);
    } else if(pik ==0){
        printf("SOu filho e o calor de exemplo eh %d que eh o original", exemplo);
    }
    
    
    return 0;
}