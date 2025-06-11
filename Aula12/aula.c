#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>


int main(void){
    /*
    1cirar chave ftok
    2criar
    3vinculação enter a memorriac comp e ponteiro local
    */
    //3333
    char* ptr;
   //1111111111111se usar o memsmo parametro vai crirar a mesma chave para que o processos assecem a mesma região
   key_t key = ftok("/bin", 'A');

   //idencificador da região de mem comp, 0644 uso padrao
   //2222222222222ipccreat que cria a região de memora compar
    int shmid = shmget(key, 1024, 0644||IPC_CREAT);
    //33333
    ptr = shmat(shmid, (void *)0, 0);


    //destruri - desvinfular a região da var local
    //devencla
    shmdt(ptr);

    //para reamente destruir
    shmctl(shmid, IPC_RMID, NULL);




    

    return 0;
}