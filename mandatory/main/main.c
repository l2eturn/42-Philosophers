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

int main(int ac, char **av)
{
	pthread_t			philos[MAX_PHILOSOPHERS];
	pthread_mutex_t		forks[MAX_FORKS];
	t_shared			shared;
	int					numb_philos;

	is_valid_input(ac, av);
	numb_philos = (int)ft_atoi(av[1]);
	shared_time_init(ac, av, &shared);
	// philos = malloc(sizeof(pthread_t) * numb_philos);
	// forks = malloc(sizeof(pthread_mutex_t) * numb_philos);
	printf("time to die: %zu\ntime to eat: %zu\ntime to sleep: %zu\n",shared.time_to_die, shared.time_to_eat, shared.time_to_sleep);
}
