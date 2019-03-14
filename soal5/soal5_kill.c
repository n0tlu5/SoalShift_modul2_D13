#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>

int main(){
    char pidline[1024];
    FILE *fp = popen("pidof soal5","r");
    fgets(pidline,1024,fp);
    
    kill(atoi(pidline), SIGKILL);
}