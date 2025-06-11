#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

int contador = 0;

int myLen(char *buf){
    int i = 0;
    while (buf[i] != '\0'){ i++;}
    return i;
}

void ctrlz( int signum){
    write(1, "Você apertou Ctl-C ", myLen("Você apertou Ctl-C "));
    int vezes = contador + '0';
    write(1, &vezes, sizeof(int));
    write(1, " vezes", myLen(" vezes"));
}

void ctrlc( int signum){
    contador++;
    if(contador==3){
        char opcao;

        write(1, "\nRealmente deseja sair? [Y/n]: ", myLen("Realmente deseja sair? [Y/n]: "));
        alarm(20);
        read(1, &opcao, 1);

        if( opcao == 'y' ||opcao == 'Y'){
            exit(0);
        }else if(opcao == 'n' ||opcao == 'N'){
            contador=0;
            alarm(0);
            write(1, "Continuando...\n", myLen("Continuando...\n"));
        }
    }


}

void tempo(int signum){
    write(1, "Demorou muito para responder. Saindo......", myLen("Demorou muito para responder. Saindo......"));
    exit(0);
}

int main(void){

    
    
    while (1){
        signal(SIGTSTP, ctrlz);
        signal(SIGINT, ctrlc);
        signal(SIGALRM, tempo);
        pause();
    }
    
    


  return 0;
}
