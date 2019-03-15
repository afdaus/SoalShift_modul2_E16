#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <syslog.h>
#include <string.h>
#include <sys/stat.h>

int main()
{
	pid_t pid, sid;
  	pid = fork();
  	if (pid < 0)
	{
    		exit(EXIT_FAILURE);
  	}
  	if (pid > 0)
	{
    		exit(EXIT_SUCCESS);
  	}
	umask(0);
	sid = setsid();
  	if (sid < 0)
	{
    		exit(EXIT_FAILURE);
	}

  	if ((chdir("/home/bastian/log")) < 0)
	{
   		 exit(EXIT_FAILURE);
  	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

  	while(1)
	{
		//init
    		char simpen[20];
		char simpen1[50];
		char lognya[100];
        	char namalog[50];
		char karakter;
		//pid_t pid1;
		//ambil jam dari system
		time_t jamskrg = time(NULL);
		//simpen sesuai format
        	strftime(simpen, 20, "%d-%m-%Y-%H:%M", localtime(&jamskrg));
		//ambil direktori
		strcpy(simpen1,"/home/bastian/log/");
		//totalin direktori
		strcat(simpen1,simpen);
		strcpy(lognya,"/var/log/syslog");
		//init file
		FILE *filelog;
		//char *dir[3] = {"mkdir",simpen1, NULL};
		int tunggu;
		int x;
		//init file
		FILE *nulislog;
		//bikin direktori
		mkdir(simpen1, S_IRWXU | S_IRWXG | S_IRWXO);
		x=30;
		int i;
		i=0;
		while(x>=0)
		{
			if(i==0)
			{
				i++;
				sleep(60);
			}
			else
			{
			//buat nama file log nya
			sprintf(namalog,"%s/log%d.log",simpen1,i);
			//buka lognya
			filelog = fopen(lognya,"r");
			//tulis ke lognya
			nulislog= fopen(namalog,"w");
			//kopi dari log asli ke log baru
			while(!feof(filelog))
			{
				karakter=fgetc(filelog);
				fputc(karakter,nulislog);
			}
			//tutup filenya
			fclose(filelog);
			//decrement x
			x--;
			fclose(nulislog);
			//increment i
			i++;
			//tunggu 1 menit
			sleep(60);
			}
		}
	}
 	exit(EXIT_SUCCESS);
}
