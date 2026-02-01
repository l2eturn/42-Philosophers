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

typedef struct s_shared
{
    long            time_to_die;
    int             stop;
    pthread_mutex_t stop_mutex;
}   t_shared;

typedef struct s_philo
{
    int             id;
    long            last_meal;
    pthread_mutex_t meal_mutex;
    t_shared        *shared;
}   t_philo;

void *philo_routine(void *arg)
{
    t_philo *p = (t_philo *)arg;

    while (1)
    {
        pthread_mutex_lock(&p->meal_mutex);
        p->last_meal = get_time_ms();
        pthread_mutex_unlock(&p->meal_mutex);

        printf("Philo %d is eating\n", p->id);
        usleep(200000);

        printf("Philo %d is sleeping\n",p->id);
        usleep(200000);
    }
    return NULL;
}

void *monitor_routine(void *arg)
{
    t_philo *p = (t_philo *)arg;
    long now;

    while (1)
    {
        pthread_mutex_lock(&p->meal_mutex);
        now = get_time_ms();
        if (now - p->last_meal > p->shared->time_to_die)
        {
            pthread_mutex_lock(&p->shared->stop_mutex);
            p->shared->stop = 1;
            pthread_mutex_unlock(&p->shared->stop_mutex);

            printf("Philo %d died\n", p->id);
            pthread_mutex_unlock(&p->meal_mutex);
            return NULL;
        }
        pthread_mutex_unlock(&p->meal_mutex);
        usleep(1000);
    }
}

int main(void)
{
    pthread_t philo_t, monitor_t;
    t_shared shared;
    t_philo philo;

    shared.time_to_die = 500;
    shared.stop = 0;
    pthread_mutex_init(&shared.stop_mutex, NULL);

    philo.id = 1;
    philo.last_meal = get_time_ms();
    pthread_mutex_init(&philo.meal_mutex, NULL);
    philo.shared = &shared;

    pthread_create(&philo_t, NULL, philo_routine, &philo);
    pthread_create(&monitor_t, NULL, monitor_routine, &philo);

    pthread_join(philo_t, NULL);
    pthread_join(monitor_t, NULL);
    return 0;
}
