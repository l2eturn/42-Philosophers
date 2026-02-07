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
		else if ((i != 1) && (i != 5) && (num < 1 || num > INT_MAX))
			error_message("Invalid Input Format4\n", 1);
		i ++;
	}
}

int	main(int ac, char **av)
{
	t_philosopher		philos[MAX_PHILOSOPHERS];
	pthread_mutex_t		forks[MAX_FORKS];
	t_shared			shared;
	pthread_t			mornitor;
	int					i;

	is_valid_input(ac, av);
	shared_time_init(ac, av, &shared);
	main_helper(&shared, philos, forks, ft_atoi(av[1]));
	pthread_create(&mornitor, NULL, mornitor_routine, philos);
	i = 0;
	while (i < shared.num_philos)
		pthread_join(philos[i++].thread, NULL);
	pthread_join(mornitor, NULL);
	cleanup_program(&shared, forks);
	return (0);
}
