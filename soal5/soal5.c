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

    if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    int count=30;

    while(1) {
        char myFile[50];
        if(count == 30){
            count=1;

            char dateTime[20];
            time_t timer = time(NULL);
            strftime(dateTime, 20, "%d:%m:%Y-%H:%M", localtime(&timer));
            sprintf(myFile,"/home/mungkin/log/%s/",dateTime);

            if(chdir(myFile)<0){
                mkdir(myFile, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                chdir(myFile);
            }
            continue;
        }
        
        FILE *fin, *fout;
        char myString[4096];

		fin = fopen("/var/log/syslog","r");
        sprintf(myFile,"log%d.log",count);
		fout = fopen(myFile,"a");

		if (fin != NULL){
			if (fout != NULL){
				while ( fgets (myString , 4095 , fin) != NULL ) fputs (myString, fout);
				fclose (fout);
			}
			fclose (fin);
		}
        count++;
        sleep(60);
    }  
    exit(EXIT_SUCCESS);
}