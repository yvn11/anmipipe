/*
 * =====================================================================================
 *
 *       Filename:  anmipipe.c
 *
 *    Description:  a demonstration of pipe system call
 *
 *        Version:  1.0
 *        Created:  27/12/12 15:28:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Zex (zex), top_zlynch@yahoo.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

#define SBUF 128

void try_pipe()
{
  int pfd[2];
	pid_t child;
	char* str = "pipe string: This'll end\n";
	char buf;
	int status;

	pipe(pfd);

	if ((child = fork()) == -1) {
		perror("fork");
	} else if (child != 0) { /* This's parent speaking*/
		printf ("This's parent speaking\n");
		close(pfd[0]);
		write(pfd[1], str, strlen(str));
		close(pfd[1]);
		wait(&status);
	} else { /* This's child speaking */
		printf ("This's child speaking\n");
		close(pfd[1]);
		while (read(pfd[0], &buf, 1))
			write(STDOUT_FILENO, &buf, 1);
		close(pfd[0]);
		
#ifdef  _PC_NAME_MAX
		printf("NAME_MAX: [%ld]\n", fpathconf(pfd[1], _PC_NAME_MAX));
#endif
#ifdef _PC_LINK_MAX
		printf("LINK_MAX: [%ld]\n", pathconf("/tmp", _PC_LINK_MAX));
#endif
#ifdef _SC_TTY_NAME_MAX
		printf("TTY_NAME_MAX: [%ld]\n", sysconf(_SC_TTY_NAME_MAX));
#endif
#ifdef _SC_PAGESIZE
		printf("PAGESIZE: [%ld]\n", sysconf(_SC_PAGESIZE));
#endif
#ifdef _PC_PIPE_BUF
		printf("PIPE_BUF: [%ld]\n", pathconf("/usr/src", _PC_PIPE_BUF));
#endif
#ifdef _SC_OPEN_MAX
		printf("OPEN_MAX: [%ld]\n", sysconf(_SC_OPEN_MAX));
#endif
#ifdef _PC_PATH_MAX
		printf("PATH_MAX: [%ld]\n", fpathconf(pfd[0], _PC_PATH_MAX));
#endif
	}
}

void try_popen_pclose()
{
	FILE *pr = popen("ls", "r");
	FILE *fw = fopen("genby_anmipipe", "w+");
	char buf[SBUF];

	while (fgets(buf, SBUF, pr))
		fputs(buf, fw);

	pclose(pr);
	fclose(fw);
}

int main(int argc, const char *argv[])
{
	try_pipe();
	try_popen_pclose();
	return 0;
}
