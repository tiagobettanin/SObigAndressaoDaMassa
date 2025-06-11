#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(void){
    //retorna u pid - retorna par ao processo pai o pid do filho, nesse momento o pid do filho retonra a 0(não que ele tenha só vai retornas)
    int pid = fork();

    if(pid != 0){
        printf("Sou um processo pai. %d %d\n", pid, getpid()); //o primeiro %d é o fork, o pai receve o pid do filho
    } else{
        printf("Sou um processo filho %d %d\n", pid, getpid());
    }
    

    return 0;
}