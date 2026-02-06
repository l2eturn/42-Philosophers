/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 23:51:41 by slimvutt          #+#    #+#             */
/*   Updated: 2026/02/06 23:51:41 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*routine(void *arg)
{
	t_philosopher   *p;

	p = arg;

	if (p->shared->num_philos == 1)
	{
		pthread_mutex_lock(p->left_fork);
		safe_print(p, "has taken a fork");
		general_usleep(p->shared->time_to_die, p->shared); 
		pthread_mutex_unlock(p->left_fork);
		while (!is_stop(p->shared))
			usleep(100); 
		return (NULL);
	}
	pthread_mutex_lock(&p->shared->meal_mutex);
	p->last_meal = get_time_ms();
	pthread_mutex_unlock(&p->shared->meal_mutex);
	if (p->id % 2 == 0)
		usleep(1000);
	while (!is_stop(p->shared))
	{
		eat(p);
		if (is_stop(p->shared))
			break;
		safe_print(p, "is sleeping");
		general_usleep(p->shared->time_to_sleep, p->shared);
		if (is_stop(p->shared))
			break;
		safe_print(p, "is thinking");
		if (p->shared->num_philos % 2 != 0) 
			usleep(3000);
	}
	return (NULL);
}

void    *mornitor_routine(void *arg)
{
    t_philosopher	*p;
    int				i;
    int				finished_eating;
    size_t			time_now;

	p = (t_philosopher *)arg;
	while (!is_stop(p[0].shared))
	{
		i = 0;
		finished_eating = 0;
		while (i < p[0].shared->num_philos)
		{
			pthread_mutex_lock(&p[i].shared->meal_mutex);
			time_now = get_time_ms();
			if (time_now - p[i].last_meal >= p[i].shared->time_to_die)
			{
				pthread_mutex_lock(&p[i].shared->print_mutex);
				printf("%zu %d died\n", time_now - p[i].shared->time_start, p[i].id);
				pthread_mutex_unlock(&p[i].shared->print_mutex);
				mornitor_stop(p[i].shared);
				pthread_mutex_unlock(&p[i].shared->meal_mutex);
				return (NULL);
			}
			if (p[i].shared->must_eat != -1 && p[i].eat_count >= p[i].shared->must_eat)
				finished_eating++;
			pthread_mutex_unlock(&p[i].shared->meal_mutex);
			i++;
		}
		if (p[0].shared->must_eat != -1 && finished_eating == p[0].shared->num_philos)
		{
			mornitor_stop(p[0].shared);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
