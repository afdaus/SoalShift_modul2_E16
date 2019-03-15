#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//main
int main()
{
	//tunggu
	int status;
	//perintah grep
        char *grep[3] = {"grep", "[.]txt$", NULL};
	//init fork
        pid_t pid,pid2;
	//perintah ls
        char *ls[3] = {"ls", "/home/bastian/modul2/campur2", NULL};
	//fork
        pid = fork();
	//perintah unzip
        char *unzp[5] = {"unzip", "/home/bastian/campur2.zip", "-d",  "/home/bastian/modul2", NULL};
	//init pipe
        int p[2];
	//init touch
        char *sentuh[3] = {"touch", "daftar.txt", NULL};
	//piping
        pipe(p);
	//tunggu
        int tunggu;
	//init fork
	pid_t pid3;
	//tunggu
        int tunggu1;
	if(pid==0)
	{
		//touch
		//test print
		//printf("CHILD\n");
		execvp("touch",sentuh);
	}
	else
	{
		//PARENT 1
		//nunggu touch
		//while((wait(&status))>0);
		//di fork parentnya
		pid2=fork();
		if(pid2==0)
		{
			//unzip
			//test print
			//printf("CHILD 1\n");
			execvp("unzip",unzp);
		}
		else
		{
			//PARENT 2
			//di fork parentnya
			while((wait(&status))>0);
			pid3=fork();
			if(pid3==0)
			{
				//ls
				//test print
				//printf("CHILD 2\n");
				//tunggu unzip
				while((wait(&tunggu1))>0);
				//piping ls grep
				dup2(p[1], 1);
                                close(p[0]);
				//jalanin ls
                                execvp("ls", ls);
			}
			else
			{
				//grep
				//tunggu ls
				while((wait(&tunggu))>0);
				//cetak buat buka daftar.txt, di timpa
				int cetak = open("daftar.txt", O_WRONLY);
				//test print
				//printf("PARENT 3\n");
				//print grep ke daftar.txt
				dup2(cetak,1);
				//piping ls grep
                 		dup2(p[0], 0);
                 		close(p[1]);
				//jalanin grep
                 		execvp("grep", grep);
			}
		}
	}
}
