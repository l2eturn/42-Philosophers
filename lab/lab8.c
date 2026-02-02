#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stddef.h>

/* ===================== TIME ===================== */

long get_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/* ===================== STRUCT ===================== */

typedef struct s_shared
{
    int             n;
    long            time_to_die;
    long            time_to_eat;
    long            time_to_sleep;
    int             stop;
    pthread_mutex_t stop_mutex;
    pthread_mutex_t print_mutex;
    pthread_mutex_t *forks;
}   t_shared;

typedef struct s_philo
{
    int             id;
    long            last_meal;
    pthread_mutex_t meal_mutex;
    pthread_mutex_t *left;
    pthread_mutex_t *right;
    t_shared        *shared;
}   t_philo;

/* ===================== STOP ===================== */

int is_stopped(t_shared *s)
{
    int ret;

    pthread_mutex_lock(&s->stop_mutex);
    ret = s->stop;
    pthread_mutex_unlock(&s->stop_mutex);
    return ret;
}

/* ===================== PRINT ===================== */

void safe_print(t_philo *p, char *msg)
{
    pthread_mutex_lock(&p->shared->print_mutex);
    if (!is_stopped(p->shared))
        printf("%ld %d %s\n", get_time_ms(), p->id, msg);
    pthread_mutex_unlock(&p->shared->print_mutex);
}

/* ===================== PRECISE SLEEP ===================== */

void precise_sleep(long duration_ms, t_shared *shared)
{
    long start = get_time_ms();

    while (!is_stopped(shared))
    {
        if (get_time_ms() - start >= duration_ms)
            break;
        usleep(1000); // 1 ms
    }
}

/* ===================== ACTIONS ===================== */

void take_forks(t_philo *p)
{
    if (p->id % 2 == 1) // odd
    {
        pthread_mutex_lock(p->left);
        pthread_mutex_lock(p->right);
    }
    else // even
    {
        pthread_mutex_lock(p->right);
        pthread_mutex_lock(p->left);
    }
}

void put_forks(t_philo *p)
{
    pthread_mutex_unlock(p->left);
    pthread_mutex_unlock(p->right);
}

void eat(t_philo *p)
{
    take_forks(p);

    pthread_mutex_lock(&p->meal_mutex);
    p->last_meal = get_time_ms();
    pthread_mutex_unlock(&p->meal_mutex);

    safe_print(p, "is eating");
    precise_sleep(p->shared->time_to_eat, p->shared);

    put_forks(p);
}

/* ===================== PHILO ROUTINE ===================== */

void *philo_routine(void *arg)
{
    t_philo *p = (t_philo *)arg;

    while (!is_stopped(p->shared))
    {
        eat(p);
        if (is_stopped(p->shared))
            break;

        safe_print(p, "is sleeping");
        precise_sleep(p->shared->time_to_sleep, p->shared);

        safe_print(p, "is thinking");
    }
    return NULL;
}

/* ===================== MONITOR ===================== */

void *monitor_routine(void *arg)
{
    t_philo *philos = (t_philo *)arg;
    int i;

    while (!is_stopped(philos[0].shared))
    {
        i = 0;
        while (i < philos[0].shared->n)
        {
            pthread_mutex_lock(&philos[i].meal_mutex);
            if (get_time_ms() - philos[i].last_meal
                > philos[i].shared->time_to_die)
            {
                pthread_mutex_lock(&philos[i].shared->print_mutex);
                printf("%ld %d died\n",
                    get_time_ms(), philos[i].id);
                pthread_mutex_unlock(&philos[i].shared->print_mutex);

                pthread_mutex_unlock(&philos[i].meal_mutex);

                pthread_mutex_lock(&philos[i].shared->stop_mutex);
                philos[i].shared->stop = 1;
                pthread_mutex_unlock(&philos[i].shared->stop_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&philos[i].meal_mutex);
            i++;
        }
        usleep(1000);
    }
    return NULL;
}

/* ===================== MAIN ===================== */

int main(void)
{
    int i;
    pthread_t monitor;
    pthread_t *threads;
    t_philo *philos;
    t_shared shared;

    /* ----- CONFIG (ลองปรับเล่นได้) ----- */
    shared.n = 5;
    shared.time_to_die = 500;
    shared.time_to_eat = 200;
    shared.time_to_sleep = 200;
    shared.stop = 0;

    pthread_mutex_init(&shared.stop_mutex, NULL);
    pthread_mutex_init(&shared.print_mutex, NULL);

    shared.forks = malloc(sizeof(pthread_mutex_t) * shared.n);
    philos = malloc(sizeof(t_philo) * shared.n);
    threads = malloc(sizeof(pthread_t) * shared.n);

    for (i = 0; i < shared.n; i++)
        pthread_mutex_init(&shared.forks[i], NULL);

    for (i = 0; i < shared.n; i++)
    {
        philos[i].id = i + 1;
        philos[i].shared = &shared;
        philos[i].left = &shared.forks[i];
        philos[i].right = &shared.forks[(i + 1) % shared.n];
        philos[i].last_meal = get_time_ms();
        pthread_mutex_init(&philos[i].meal_mutex, NULL);
        pthread_create(&threads[i], NULL, philo_routine, &philos[i]);
    }

    pthread_create(&monitor, NULL, monitor_routine, philos);

    for (i = 0; i < shared.n; i++)
        pthread_join(threads[i], NULL);
    pthread_join(monitor, NULL);

    return 0;
}
