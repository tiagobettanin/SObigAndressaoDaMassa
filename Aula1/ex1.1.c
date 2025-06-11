#include <unistd.h>
#include <signal.h>

int contador =0;

int myLen(char *buf){
    int i=0;
    while (buf[i] != '\0'){ i++; }
    return i;
}

void ctlz(int signum){
    contador++;
    write(1, "ctlz digitado\n", myLen("ctlz digitado\n"));

}

void alarme( int sigma){

    write(1, "\n\nAlarme disparado\n\n", myLen("\n\nAlarme disparado\n\n"));

}

void printsinc(char* msg, int segundos){

    while(contador<=3){

        signal(SIGTSTP, ctlz);
        
        
        signal(SIGALRM, alarme);
        alarm(segundos);
        pause();
        
        write(1, msg, myLen(msg));

    }


}

int main(){
    
    printsinc( "\nTESTE TESTE\n", 5);



    //while(1);
    


    return 0;
}