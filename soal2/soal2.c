#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <grp.h>
#include <pwd.h>

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

  while(1) {
    // main program here
    char dir[] = "/home/panda/hatiku/elen.ku";
    char own[] = "www-data";
    struct stat su;
    struct group *gr;
    struct passwd *pw;
    
    chmod(dir, 0777);
    stat(dir, &su);

    pw = getpwuid(su.st_uid);
    gr = getgrgid(su.st_gid);
    
    if(strcmp(gr->gr_name,own)==0 && strcmp(pw->pw_name,own)==0){
//	printf("HELLO");     
	  remove(dir);
    }
    sleep(3);
  }
  exit(EXIT_SUCCESS);
}
