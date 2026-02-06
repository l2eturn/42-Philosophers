/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 01:33:10 by slimvutt          #+#    #+#             */
/*   Updated: 2025/12/21 01:33:10 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include "utils.h"
#include <limits.h>

size_t get_time_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	shared_time_init(int ac, char **av, t_shared *shared)
{
	shared->num_philos = ft_atoi(av[1]);
	shared->time_to_die = ft_atoi(av[2]);
	shared->time_to_eat = ft_atoi(av[3]);
	shared->time_to_sleep = ft_atoi(av[4]);
	shared->time_start = get_time_ms();

	shared->must_eat = -1;
	if (ac == 6)
		shared->must_eat = ft_atoi(av[5]);

	shared->stop = 0;
}

// input must take only 5,6 arg inlucde ./a.out
// ./philo number_of_philos,  time_die, time_eat, time_sleep, (extra_for_time_to_eat_each_philos)

bool	is_invalid_number(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (true);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (true);
		i++;
	}
	return (false);
}

void	is_valid_input(int ac, char **av)
{
	int		i;
	long	num;
	i = 1;
	if ((ac != 5) && (ac != 6)) 
		error_message("Argument Count Error1\n", 1);
	while (i < ac)
	{
		if (is_invalid_number(av[i]))
			error_message("Invalid Input Format2\n", 1);
		num = (long)ft_atoi(av[i]);
		if (i == 1 && (num < 1 || num > MAX_PHILOSOPHERS))
			error_message("Invalid Input Format2\n", 1);
		else if (i == 5 && (num < 0 || num > INT_MAX))
			error_message("Invalid Input Format3\n", 1);
		else if ((i != 1) &&  (i != 5) && (num < 1 || num > INT_MAX))			
			error_message("Invalid Input Format4\n", 1);		
		i ++;	
	}
}

void	forks_init(t_shared *shared, pthread_mutex_t *forks,int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i]);
			error_message("Mutex Error\n", 1);
		}
		i++;
	}
	shared->forks = forks;
}

int	shared_mutex_init(t_shared *shared)
{
	if (pthread_mutex_init(&shared->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&shared->stop_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&shared->print_mutex);
		return (1);
	}
	if (pthread_mutex_init(&shared->meal_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&shared->print_mutex);
		pthread_mutex_destroy(&shared->stop_mutex);
		return (1);
	}
	return (0);
}
int	is_stop(t_shared *shared)
{
	int	ret;

	pthread_mutex_lock(&shared->stop_mutex);
	ret = shared->stop;
	pthread_mutex_unlock(&shared->stop_mutex);
	return	(ret);
}

void	take_forks(t_philo *p)
{
	if ((p->id) % 2 == 1)
	{
		pthread_mutex_lock(p->left_fork);
		pthread_mutex_lock(p->right_fork);
	}
	else
	{
		pthread_mutex_lock(p->right_fork);
		pthread_mutex_lock(p->left_fork);
	}
}

void put_forks(t_philo *p)
{
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

void	eat(t_philo *p)
{
	take_forks(p);
	pthread_mutex_lock(&p->shared->meal_mutex);
	p->last_meal = get_time_ms();
	pthread_mutex_unlock(&p.shared->meal_mutex);

	put_forks(p);
}

void	*routine(void *arg)
{
	t_philosopher *p

	p = arg;
	printf("print from philo(s) ID : %d\n", p->id);
	usleep(2);
	return (NULL);
}

void	philos_init(t_philosopher *philos, t_shared *shared, int numb_philos)
{
	int	i;

	i = 0;
	while (i < numb_philos)
	{
		philos[i].id = i + 1;
		philos[i].eat_count = 0;
		philos[i].last_meal = shared->time_start;

		philos[i].left_fork = &shared->forks[i];
		philos[i].right_fork = &shared->forks[(i + 1) % numb_philos];
		philos[i].shared = shared;
		i ++;
	}
}

int	philos_create_threads(t_philosopher *philos, int numb_philos)
{
	int	i;

	i = 0;
	while (i < numb_philos)
	{
		if (pthread_create(&philos[i].thread, NULL, routine, &philos[i]) != 0)
		{
			while (--i >= 0)
				pthread_join(philos[i].thread, NULL);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*mornitor_routine(void *arg)
{
	t_philosopher	*p;

	p = arg;

	return (NULL);
}

int main(int ac, char **av)
{
	t_philosopher		philos[MAX_PHILOSOPHERS];
	pthread_mutex_t		forks[MAX_FORKS];
	t_shared			shared;
	pthread_t			mornitor;
	int					numb_philos;

	is_valid_input(ac, av);
	numb_philos = (int)ft_atoi(av[1]);
	shared_time_init(ac, av, &shared);
	shared_mutex_init(&shared);
	forks_init(&shared, forks, numb_philos);
	philos_init(philos, &shared, numb_philos);
	philos_create_threads(philos, numb_philos);
	// philos = malloc(sizeof(pthread_t) * numb_philos);
	// forks = malloc(sizeof(pthread_mutex_t) * numb_philos);
	printf("time to die: %zu\ntime to eat: %zu\ntime to sleep: %zu\n",shared.time_to_die, 
		shared.time_to_eat, shared.time_to_sleep);
	//error test
	for (int i = 0; i < numb_philos ; i++)
		printf("Philo(s) ID: %d\n", philos[i].id);

	//pid and thread numbers check;
	for (int i = 0; i < numb_philos ; i++)
		pthread_join(philos[i].thread,NULL);
}
