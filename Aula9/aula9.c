#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main(){
    if(fork() > 0){
        printf("Sou codigo pai\n");
        wait(NULL);
    }else{
        printf("Sou codigo filho, vou rodar o ls\n");
        execl("/bin/ps", "ps","-aux", NULL);//caminho para os executaveis    para metro para mostarar    apartir do segundo parametro pode passar uma lista de artumgento tem que ter NULL no final para informor que acabou os argumetnos
        //execl("/bin/ls", "ls","-l", NULL);
        //"ps"ps" "-aux"
    }


    return 0;
}