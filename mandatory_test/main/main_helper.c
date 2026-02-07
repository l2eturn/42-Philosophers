/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 12:53:50 by slimvutt          #+#    #+#             */
/*   Updated: 2026/02/07 12:53:50 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	main_helper(t_shared *shared, t_philosopher *philos,
			pthread_mutex_t *forks, int numb_philos)
{
	int			i;

	shared_mutex_init(shared);
	forks_init(shared, forks, numb_philos);
	philos_init(philos, shared, numb_philos);
	shared->time_start = get_time_ms();
	i = 0;
	while (i < numb_philos)
	{
		philos[i].last_meal = shared->time_start;
		i ++;
	}
	philos_create_threads(philos, numb_philos);
}

void	cleanup_program(t_shared *shared, pthread_mutex_t *forks)
{
	int i;

	i = 0;
	while (i < shared->num_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&shared->print_mutex);
	pthread_mutex_destroy(&shared->stop_mutex);
	pthread_mutex_destroy(&shared->meal_mutex);
}
