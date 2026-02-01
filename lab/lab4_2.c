#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t print_mutex;

void *routine(void *arg)
{
    int id = *(int *)arg;
    int i = 0;

    while (i < 5)
    {
        pthread_mutex_lock(&print_mutex);
        printf("Philo %d is EATING\n", id);
        pthread_mutex_unlock(&print_mutex);

        usleep(1000);
        i++;
    }
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;
    int a = 1, b = 2;

    pthread_mutex_init(&print_mutex, NULL);

    pthread_create(&t1, NULL, routine, &a);
    pthread_create(&t2, NULL, routine, &b);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&print_mutex);
    return 0;
}
