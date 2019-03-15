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
	//kill programnya
	char *bunuh[3] = {"pkill", "soal5", NULL};
	execvp("pkill",bunuh);
}
