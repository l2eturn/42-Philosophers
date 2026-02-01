#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_philo
{
    int             id;
    pthread_mutex_t *left;
    pthread_mutex_t *right;
}   t_philo;

void take_forks(t_philo *p)
{
    if (p->id % 2 == 1) // odd
    {
        pthread_mutex_lock(p->left);
        printf("Philo %d took LEFT fork\n", p->id);
        usleep(100000);
        pthread_mutex_lock(p->right);
        printf("Philo %d took RIGHT fork\n", p->id);
    }
    else // even
    {
        pthread_mutex_lock(p->right);
        printf("Philo %d took RIGHT fork\n", p->id);
        usleep(100000);
        pthread_mutex_lock(p->left);
        printf("Philo %d took LEFT fork\n", p->id);
    }
}

void put_forks(t_philo *p)
{
    pthread_mutex_unlock(p->left);
    pthread_mutex_unlock(p->right);
}

void *philo_routine(void *arg)
{
    t_philo *p = (t_philo *)arg;

    while (1)
    {
        take_forks(p);
        printf("Philo %d is EATING\n", p->id);
        usleep(200000);

        put_forks(p);
        printf("Philo %d is SLEEPING\n", p->id);
        usleep(200000);
    }
    return NULL;
}

int main(void)
{
    pthread_t t1, t2;
    pthread_mutex_t forks[2];
    t_philo p1, p2;

    pthread_mutex_init(&forks[0], NULL);
    pthread_mutex_init(&forks[1], NULL);

    p1.id = 1;
    p1.left = &forks[0];
    p1.right = &forks[1];

    p2.id = 2;
    p2.left = &forks[1];
    p2.right = &forks[0];

    pthread_create(&t1, NULL, philo_routine, &p1);
    pthread_create(&t2, NULL, philo_routine, &p2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
