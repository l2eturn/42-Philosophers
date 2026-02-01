#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//void *print_numbers(void *arg)
//{
//    int i = 0;
//    char *name = (char *)arg;

//    while (i < 5)
//    {
//        printf("%s: %d\n", name, i);
//        usleep(100);
//        i++;
//    }
//    return NULL;
//}

//int main(void)
//{
//    pthread_t t1, t2;

//    pthread_create(&t1, NULL, print_numbers, "A");
//    pthread_create(&t2, NULL, print_numbers, "B");

//    pthread_join(t1, NULL);
//    pthread_join(t2, NULL);
//    return 0;
//}


#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t print_mutex;

void *print_numbers(void *arg)
{
    int i = 0;
    char *name = (char *)arg;

    while (i < 5)
    {
        pthread_mutex_lock(&print_mutex);
        printf("%s: %d\n", name, i);
        pthread_mutex_unlock(&print_mutex);
        usleep(100);
        i++;
    }
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    pthread_mutex_init(&print_mutex, NULL);

    pthread_create(&t1, NULL, print_numbers, "A");
    pthread_create(&t2, NULL, print_numbers, "B");

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&print_mutex);
    return 0;
}

