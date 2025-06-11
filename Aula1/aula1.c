#include <unistd.h>

int myLen(char *buf){
    int i=0;
    while (buf[i] != '\0'){ i++; }
    return i;
}

void myPrintf( int x, int y, char *msg){

    char str[] = "\033[ B\033[ C";
    str[2] = x + '\0';
    str[6] = y + '\0';

    write( 1, str, myLen(str));
    write( 1, str, myLen(msg));

}

int main(){
    /*
    write( 1, "Hello word em posix\n", myLen("Hello word em posix\n"));

    myPrintf( 5, 5, "Hello word em posix\n");
    */

    

    return 0;
}