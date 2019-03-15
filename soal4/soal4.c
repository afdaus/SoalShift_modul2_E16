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

  int count=1;
  while(1) 
  {
    char dir[]="/home/panda/Documents/makanan/makan_enak.txt";
    struct stat sb;
    stat(dir, &sb);
    
    if(sb.st_atime + 30 > time(NULL))
    {
      char new[100];
      sprintf(new, "%d.txt", count);

      char dir2[]="/home/panda/Documents/makanan/makan_sehat";
      strcat(dir2, new);
      
      FILE *tmp = fopen(dir2, "w"); 
      fclose(tmp);
      count++;
    }
    sleep(5);
  }
  exit(EXIT_SUCCESS);
}
