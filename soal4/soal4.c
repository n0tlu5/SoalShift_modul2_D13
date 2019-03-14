#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

void modify_without_modifying(char* fileName){
    FILE* fin;
    fin = fopen(fileName,"a");
    fprintf(fin,"x");
    fseeko(fin,-1,SEEK_END);
    int position = ftello(fin);
    ftruncate(fileno(fin), position);
    fclose(fin);
}

int main() {
    pid_t pid, sid;

    pid = fork();

    if (pid < 0) {
    exit(EXIT_FAILURE);
    }

    if (pid > 0) {
    exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();

    if (sid < 0) {
    exit(EXIT_FAILURE);
    }

    if ((chdir("/home/mungkin/Documents/makanan/")) < 0) {
    exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    FILE *fin;
    char fileKu[] = "makan_enak.txt";
    
    modify_without_modifying(fileKu);
    
    while(1) {
        struct stat info;
        
        if(!stat(fileKu, &info)){
            double seconds;
            time_t timer;

            timer=time(NULL);
            seconds = difftime(timer, info.st_atime);
            
            if(seconds<=30.0){
                char newName[256]="makanan_sehat1.txt";
                int count=1;

                modify_without_modifying(fileKu);
                
                while(fin=fopen(newName,"r")){
                    fclose(fin);
                    count++;
                    sprintf(newName,"makanan_sehat%d.txt",count);
                }
                
                fin = fopen(newName, "w");
                fclose(fin);
            }
        }
        sleep(5);
    }  
    exit(EXIT_SUCCESS);
}