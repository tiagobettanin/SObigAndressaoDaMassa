#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

int contador = 0;

int myLen(char *buf){
    int i = 0;
    while (buf[i] != '\0'){ i++;}
    return i;
}

void ctrlBarra( int signum){
    //write(1, "\n\nAcabou\n\n", myLen("\n\nAcabou\n\n"));
    alarm(2);
    
}

void alarme(int signum){
    write(1, "Saindo.", myLen("Saindo."));
    exit(0);
}

int main(void){
    
    while(1){
        signal(SIGALRM, alarme);
        signal(SIGQUIT, ctrlBarra);
        
        pause();
    }


  return 0;
}
