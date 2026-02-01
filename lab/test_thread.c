#include <stdio.h>
#include <pthread.h>


void *print_hello(void *av)
{
	printf("Hello %s\n", (char *)av);
}

int main(int ac, char **av)
{
	if (ac == 3)
	{
		pthread_t thread1, thread2;
		if (pthread_create(&thread1, NULL, print_hello, (void *)av[1]))
			printf("Error");
		if (pthread_create(&thread2, NULL, print_hello, (void *)av[2]))
			printf("Error");
		pthread_join(thread1,NULL);
		pthread_join(thread2,NULL);
	}
	return 0;
}
