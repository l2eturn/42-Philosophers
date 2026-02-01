#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//int main(void)
//{
//	pid_t pid = fork();

//	if (pid == 0)
//		printf("This is the Child-Process , and This is PID %d\n", getpid());
//	else if (pid > 0)
//		printf("This is the Parent-Process , and This is PID %d\n", getpid());
//	else{
//		printf("fork error\n");
//		return 1;
//	}
//	return 0;
//}

//no wait

//int main(void)
//{
//	pid_t pid = fork();

//	if (pid == 0)
//		execlp("/bin/ls","ls",NULL);
//	else if (pid > 0)
//		printf("Child-Process is finished\n");
//	else{
//		printf("fork error\n");
//		return 1;
//	}
//	return 0;
//}

//int main(void)
//{
//	pid_t pid = fork();

//	if (pid == 0)
//		execlp("/bin/ls","ls",NULL);
//	else if (pid > 0)
//	{
//		int status;
//		waitpid(pid, &status, 0);
//		printf("Child-Process is finished\n");
//	}
//	else{
//		printf("fork error\n");
//		return 1;
//	}
//	return 0;
//}

int main(void)
{
	pid_t pid = fork();
	char *args[] = {"ls","-la",'\0'}; 
	//if (pid == 0)
	//	execlp("/bin/ls","ls",NULL);
	if (pid == 0)
	{
		execvp("ls",args);
		printf("This will not be print\n");
	}
	else if (pid > 0)
	{
		int status;
		waitpid(pid, &status, 0);
		printf("Child-Process is finished\n");
	}
	else{
		printf("fork error\n");
		return 1;
	}
	return 0;
}

