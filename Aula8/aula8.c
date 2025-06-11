#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char *message = "This is a message!!!" ; 
char *message2 = "This is a message2!!" ; 

void main(){
    char buf[1024];
    char buf2[1024];

    int fd[2];
    pipe(fd); /*create pipe*/

    int fd2[2];
    pipe(fd2); /*create pipe*/

    if (fork() != 0) { /* I am the parent */

        write(fd[1], message, strlen (message) + 1) ;
        //read(fd2[0], buf2, 1024) ;
        //printf("Got this from MaMa!!: %s\n", buf2) ;

    }else { /*Child code */

        //write(fd2[1], message2, strlen (message2) + 1) ;
        read(fd[0], buf, 1024) ;
        printf("Got this from MaMa!!: %s\n", buf) ;
    
    }
    
}