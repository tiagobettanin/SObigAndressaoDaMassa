/******************************************************************************

Faça um programa para disparar uma mensagen de bons estudos a cada 10 segundos 
utilizando a API posix do linux.

*******************************************************************************/
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(void){
    int pid = fork();
    int x = 10;
    
    if( pid > 0){
        x=x+10;
        printf("Sou pai e o valor de x eh: %d\n", x);
        wait(NULL);
    }else if(  pid == 0){
        execl("/bin/ps", "ps", "-l", NULL);
        printf("Sou filho e o valor de x eh: %d\n", x);

    }
    
    
    return 0;
}
