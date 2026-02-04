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

// input must take only 5,6 arg inlucde ./a.out
// ./philo number_of_philos time_die time_eat time_sleep (extra_for_time_to_eat_each_philos)

void	valid_input(int ac, char **av)
{
	int	i;

	i = 1;
	if ((ac != 5) && (ac != 6)) 
		error_message("Invalid Input Format\n", 1);
	while (i ++)
	{




	}
	if ()
		error_message("Invalid Input Format\n", 1);
		
}

int main(int ac, char **av)
{
	pthread_t			*philos;
	pthread_mutex_t		*forks;
	t_shared			shared;
	int					numb_philos;

	valid_input(ac, av);
	// numb_philos = (int)ft_atoi(av[1]);
	// philos = malloc(sizeof(pthread_t) * numb_philos);
	// forks = malloc(sizeof(pthread_mutex_t) * numb_philos);
}
