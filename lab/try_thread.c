#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void *routine()
{
	printf("Hello from Thread\n");
}


int main(void)
{
	pthread_t t1;
	pthread_create(&t1,NULL,routine,NULL);
	pthread_join(t1,NULL);
}