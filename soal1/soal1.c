#include <dirent.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <sys/wait.h>

bool ext_match(const char *name, const char *ext){
	size_t nl = strlen(name), el = strlen(ext);
	return nl >= el && !strcmp(name + nl - el, ext);
}

void getNewName(char* mystr) {
	unsigned int x,len;
	len = strlen(mystr);

	for (x = (len - 4); x < len; x++)
		mystr[x]='\0';

	char meh[10]="_grey.png";
	strcat(mystr,meh);
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

	if ((chdir("/")) < 0) {
		exit(EXIT_FAILURE);
	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	DIR *dp;
	struct dirent *ep;

	while(1) {
		dp = opendir ("/home/mungkin/Downloads/");
		if (dp != NULL){
		while (ep = readdir (dp))
			if(ext_match(ep->d_name, ".png")){
				unsigned char isFolder =0x4;
				if(ep->d_type == isFolder) continue;
				pid_t child_id;
				int status;
				char new[256];

				strcpy(new,ep->d_name);
				getNewName(new);

				char fromDir[256]="/home/mungkin/Downloads/";
				char toDir[256]="/home/mungkin/modul2/gambar/";

				strcat(toDir, new);
				strcat(fromDir, ep->d_name);

			

				child_id = fork();

				if(child_id==0){
					char *argv[4] = {"mv", fromDir, toDir, NULL};
    				execv("/bin/mv", argv);
				}else{
					while ((wait(&status)) > 0);
					int status = remove(fromDir);
				}
			}
			(void) closedir (dp);
		}
		sleep(60);
	}  
	exit(EXIT_SUCCESS);
}