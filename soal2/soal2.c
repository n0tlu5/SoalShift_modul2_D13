#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(777);

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

  while(1) {
    struct stat info;
    char fileKu[] = "/home/mungkin/hatiku/elen.ku";
    if(!stat(fileKu, &info)){
        struct passwd *pw = getpwuid(info.st_uid);
        struct group  *gr = getgrgid(info.st_gid);

        if(!strcmp(pw->pw_name, "www-data") && !strcmp(gr->gr_name, "www-data")){
            chmod(fileKu, S_IRWXU|S_IRWXG|S_IRWXO);
            int status = remove(fileKu);
        }       
    }
    sleep(3);
  }  
  exit(EXIT_SUCCESS);
}