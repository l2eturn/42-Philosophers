#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *routine(void *arg)
{
    int id = *(int *)arg;
    int i = 0;

    while (i < 5)
    {
        printf("Philo %d is ", id);
        usleep(1000);
        printf("EATING\n");
        i++;
    }
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;
    int a = 1, b = 2;

    pthread_create(&t1, NULL, routine, &a);
    pthread_create(&t2, NULL, routine, &b);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
