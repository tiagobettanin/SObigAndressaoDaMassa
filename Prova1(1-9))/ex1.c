/******************************************************************************

Faça um programa para disparar uma mensagen de bons estudos a cada 10 segundos utilizando a API posix do linux.

*******************************************************************************/
#include <unistd.h>
#include<signal.h>

int myLen(char *msg){
    int i=0;
    while(  msg[i] != '\0' ){i++;}
    
    return i;
}

void alarme(){
    write( 1, "BONS ESTUDOS!\n", myLen("BONS ESTUDOS!\n"));
}

int main(){
    int i=0;
    while( i < 10){
        signal(SIGALRM, alarme);
        alarm(10);
        pause();
        i++;
    }

    return 0;
}
