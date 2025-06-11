#include <unistd.h>
#include <signal.h>

int myLen(char *buf){
    int i=0;
    while (buf[i] != '\0'){ i++; }
    return i;
}

void ctlz(int signum){

    write(1, "ctlz digitado\n", myLen("ctlz digitado\n"));

}

void alarme( int sigma){

    write(1, "\n\nAlarme disparado\n\n", myLen("\n\nAlarme disparado\n\n"));

}

void printsinc(char* msg, int segundos){
    int contador=0;

    while(contador<=3){

        signal(SIGTSTP, ctlz);
        signal(SIGALRM, alarme);

        

    }


}

int main(){
    
    

    alarm(5);
    pause();

    //while(1);
    


    return 0;
}