#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>

////////////////////////////////////////////estudar isso


//sincronizar pai e filho pelo wait

int main(void){
    //status receve uma iteira e revela uma word(arquitetura (materia))
    int pid, status;
    pid = fork();

    if(pid == 0){
        printf("Filho, %d\n", getpid());
        //while(1);//kill, tem que a abrir o cmd e kill 'pid do filho'
        exit(10);//comunica com o wait
    }else if(pid > 0){
        wait(&status);

        //verificar se o processo acabou beme como acabou)(normal)(filho, TEM QUE CAIR NO EXIT), e aplica a mascara de bits
        if(WIFEXITED(status)){
            printf("Filho executrou normalamente, %d: %d\n", getpid(), WEXITSTATUS(status));
        }

        //processo morto por alguem
        if(WIFSIGNALED(status)){
            printf("Processo filho sofreu um kill %d\n", status);
        }

        printf("Pai, %d\n", getpid());
    }else if(pid < 0){
        printf("Erro na criação de processo\n");
    }



    return 0;
}