/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 05:20:14 by slimvutt          #+#    #+#             */
/*   Updated: 2025/12/21 05:20:14 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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

void	forks_init(t_shared *shared, pthread_mutex_t *forks, int num_philos)
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
