#include <sys/time.h>
#include <stddef.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define N 1

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
    pthread_mutex_t print_mutex;
}   t_shared;

typedef struct s_philo
{
    int             id;
    long            last_meal;
    pthread_mutex_t meal_mutex;
    t_shared        *shared;
}   t_philo;

/* ---------- helpers ---------- */

int is_stopped(t_shared *s)
{
    int ret;

    pthread_mutex_lock(&s->stop_mutex);
    ret = s->stop;
    pthread_mutex_unlock(&s->stop_mutex);
    return ret;
}

void safe_print(t_philo *p, char *msg)
{
    pthread_mutex_lock(&p->shared->print_mutex);
    if (!is_stopped(p->shared))
        printf("%ld %d %s\n", get_time_ms(), p->id, msg);
    pthread_mutex_unlock(&p->shared->print_mutex);
}

/* ---------- philosopher ---------- */

void eat(t_philo *p)
{
    pthread_mutex_lock(&p->meal_mutex);
    p->last_meal = get_time_ms();
    pthread_mutex_unlock(&p->meal_mutex);

    safe_print(p, "is eating");
    usleep(200000);
}

void *philo_routine(void *arg)
{
    t_philo *p = (t_philo *)arg;

    while (!is_stopped(p->shared))
    {
        eat(p);
        if (is_stopped(p->shared))
            break;

        safe_print(p, "is sleeping");
        usleep(200000);

        safe_print(p, "is thinking");
    }
    return NULL;
}

/* ---------- monitor ---------- */

void *monitor_routine(void *arg)
{
    t_philo *philos = (t_philo *)arg;

    while (!is_stopped(philos[0].shared))
    {
        pthread_mutex_lock(&philos[0].meal_mutex);
        if (get_time_ms() - philos[0].last_meal
            > philos[0].shared->time_to_die)
        {
            pthread_mutex_lock(&philos[0].shared->print_mutex);
            printf("%ld %d died\n",
                get_time_ms(), philos[0].id);
            pthread_mutex_unlock(&philos[0].shared->print_mutex);

            pthread_mutex_unlock(&philos[0].meal_mutex);

            pthread_mutex_lock(&philos[0].shared->stop_mutex);
            philos[0].shared->stop = 1;
            pthread_mutex_unlock(&philos[0].shared->stop_mutex);
            return NULL;
        }
        pthread_mutex_unlock(&philos[0].meal_mutex);
        usleep(1000);
    }
    return NULL;
}

/* ---------- main ---------- */

int main(void)
{
    pthread_t philo_t, monitor_t;
    t_shared shared;
    t_philo  philo;

    shared.time_to_die = 100;
    shared.stop = 0;
    pthread_mutex_init(&shared.stop_mutex, NULL);
    pthread_mutex_init(&shared.print_mutex, NULL);

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
