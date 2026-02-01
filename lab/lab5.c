#include <sys/time.h>
#include <stddef.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

long get_time_ms(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

typedef struct s_philo
{
    int             id;
    long            last_meal;
    pthread_mutex_t *left;
    pthread_mutex_t *right;
}   t_philo;

void eat(t_philo *p)
{
    pthread_mutex_lock(p->left);
    pthread_mutex_lock(p->right);

    // 🔑 จุดสำคัญของแลปนี้
    p->last_meal = get_time_ms();
    printf("Philo %d starts eating at %ld\n", p->id, p->last_meal);

    usleep(200000); // simulate eating

    pthread_mutex_unlock(p->right);
    pthread_mutex_unlock(p->left);
}

void *philo_routine(void *arg)
{
    t_philo *p = (t_philo *)arg;

    while (1)
    {
        eat(p);
        printf("Philo %d is sleeping\n", p->id);
        usleep(200000);

        printf("Philo %d is thinking\n", p->id);
    }
    return NULL;
}

int main(void)
{
    pthread_t t1;
    pthread_mutex_t forks[2];
    t_philo p1;

    pthread_mutex_init(&forks[0], NULL);
    pthread_mutex_init(&forks[1], NULL);

    p1.id = 1;
    p1.left = &forks[0];
    p1.right = &forks[1];

    p1.last_meal = get_time_ms(); // initial meal time

    pthread_create(&t1, NULL, philo_routine, &p1);
    pthread_join(t1, NULL);
    return 0;
}
