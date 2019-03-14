#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

bool ext_match(const char *name, const char *ext){
	size_t nl = strlen(name), el = strlen(ext);
	return nl >= el && !strcmp(name + nl - el, ext);
}

int main( int argc, char* argv[] ) {
    pid_t child_id;
    int status,r;

    if(argc!=2){
        printf( "usage: %s filename\n", argv[0] );
    }else{
        int n = strlen(argv[1]);

        while(argv[1][n]!='/') n--;
        argv[1][n+1]='\0';

        if (chdir(argv[1]) < 0){
            exit(EXIT_FAILURE);
        }

        child_id = fork();

        if (child_id == 0) {
            char *myArg[3] = {"unzip", "campur2.zip", NULL};
            execv("/usr/bin/unzip", myArg);
        } else {
            while ((wait(&status)) > 0);
            strcat(argv[1],"campur2/");
            
            if (chdir(argv[1]) < 0){
                exit(EXIT_FAILURE);
            }
            
            pid_t child_id2;
            int status, p[2];
            char *ls[] = {"ls", argv[1], NULL};
            char *grep[] = {"grep", ".txt$", NULL};
            char *sh[] = {"sh", "-c", "cat > /home/mungkin/Documents/daftar.txt", NULL};

            pipe(p);
            child_id2=fork();

            if(child_id2==0){
                pid_t child_id3;
                int q[2];
                
                pipe(q);
                child_id3=fork();

                if(child_id3==0){

                }else{
                    close(q[1]);
                    dup2(q[0],0);
                    close(q[0]);
                    close(p[0]);
                    close(p[1]);

                    r = execv("/bin/sh", sh);                
                }
                close (p[1]);
                dup2(p[0],0);
                close (p[0]);
                close (q[0]);
                dup2(q[1],1);
                close (q[1]);

                r = execv("/bin/grep", grep);
            }else{
                close (p[0]);
                dup2(p[1],1);
                close (p[1]);

                r = execv("/bin/ls", ls);            
            }
        }    
    }
    return r;
}