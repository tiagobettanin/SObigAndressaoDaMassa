#include <unistd.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

#include<string.h>

//cossix para usar o c em vaixo nivel

char *msg;
int cont = 0;

int myLen(char *buf){
    int i=0;
    while (buf[i] != '\0'){ i++; }
    return i;
}

void printsinc(char* str, int segundos){

    strcpy(msg, str);

    while(1){
        alarm(segundos);
        pause();
    }


}

void imprime( int signum){
    write( 1, msg, myLen(msg));
}

void ctlz(int signum){
    cont++;
    if(cont ==3)
        exit(0);

}

int main(){

    msg = malloc(100*sizeof(char));
    
    //dectar o sinal sigalrm
    signal(SIGALRM, imprime);    
    signal(SIGTSTP, ctlz);

    printsinc( "\nTESTE TESTE\n", 5);


    return 0;
}