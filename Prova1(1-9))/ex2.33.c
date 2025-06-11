#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

//Auxiliar no write para verificação de tamhno de strings
int myLen(char *buf){
    int i = 0;
    while (buf[i] != '\0'){ i++;}
    return i;
}

int main (void){
    int pid = fork();
    int status;
    char resposta, l;
    
    if(pid>0){//Pai
        //Força o pai a aguardar o filho, e armazena o status de como o filho encerrou
        wait(&status);

        //Analise se o filho encerrou normalmente se sim status restorna 1 entrando no if se não continua o codigo
        if(WIFEXITED(status)){
            write(1, "Filho executrou normalamente \n", myLen("Filho executrou normalamente \n"));
        }
        //Verifica se o processo não foi encerrado normalmetne, se não foi WIFSIGNALED retorna true entrado no if
        if(WIFSIGNALED(status)){
            write(1, "Processo filho sofreu um kill \n", myLen("Processo filho sofreu um kill \n"));
        }

    } else if(pid ==0){//Filho
        //Escreve as opçeos e le a digitado pelo ususario
        write(1, "Opção 1: Entrar em um loop infinito.\nOpção 2: Encerrar-se normalmente com código de saída 0.\n", myLen("Opção 1: Entrar em um loop infinito.\nOpção 2: Encerrar-se normalmente com código de saída 0.\n"));
        read(0, &resposta, sizeof(resposta));
        read(0, &l, sizeof(l));

        //Analisa as reposta 1 é loop, e 2 encerra o porcesso filho
        if(resposta == '1'){
            while(1);
        }else if(resposta == '2'){
            exit(0);
        }


    }else if(pid < 0){//Erro na criação do processo
        write(1, "Erro na criação de processo\n", myLen("Erro na criação de processo\n"));
    }
    
    
    return 0;
}