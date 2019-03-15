#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

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

  if ((chdir("/home/samuel/kumpul/soal1")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {
     DIR *d;
  struct dirent *dir;
  char fsumber[1000];
  char bobi[5] = ".png";
  char grey[6] = "_grey";
  d = opendir(".");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
        char temp[1000]="",temp1[1000]="",temp2[1000]="",temp3[1000]="",temp4[1000]="";
        int a=0,len=0,len2=0,tes=0,i=0;
        strcpy(fsumber,dir->d_name);
        len = strlen(fsumber);
        len2 = len-4;
        //printf("%s\n",fsumber);
        for(i=len2;i<=len;++i)
        {
        temp1[a] = fsumber[i];
        a++;
        }

        tes=strcmp(temp1, bobi);
 if(tes == 0)
        {
        int b=0,c=0;
        for(c=0;c<len2;++c)
         {
                temp[b] = fsumber[c];
                b++;
         }

        strcpy(temp2,strcat((strcat(temp,grey)),temp1));

        //printf("%s", temp2);

        char alamat[100] = "/home/samuel/modul2/gambar/";
strcpy(temp3,strcat(alamat,temp2));
        rename(fsumber,temp3);

        }
        else{

        }


    }

    closedir(d);
  }

    sleep(1);
  }
  
  exit(EXIT_SUCCESS);
}
