#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct	s_philo
{
	int			id;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}				t_philo;

void *philo_routine(void *arg)
{
    t_philo *p = (t_philo *)arg;
    int i = 0;

    while (i < 3)
    {
        // take forks
        pthread_mutex_lock(p->left);
        printf("%d took left fork\n", p->id);

        pthread_mutex_lock(p->right);
        printf("%d took right fork\n", p->id);

        // eat
        printf("%d is eating\n", p->id);
        usleep(300000);

        // put forks
        pthread_mutex_unlock(p->right);
        pthread_mutex_unlock(p->left);

        // sleep
        printf("%d is sleeping\n", p->id);
        usleep(200000);

        // think
        printf("%d is thinking\n", p->id);

        i++;
    }
    return NULL;
}


int main(int ac, char **av)
{
	pthread_t t1,t2;
	pthread_mutex_t forks[2];
	t_philo p1,p2;

	pthread_mutex_init(&forks[0],NULL);
	pthread_mutex_init(&forks[1],NULL);
	//			forks[0]
	//		p1			  p2
	//			forks[1]	
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
