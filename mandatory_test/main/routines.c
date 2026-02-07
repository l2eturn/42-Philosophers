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

/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* routines.c                                         :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: 2026/02/06 23:51:41 by slimvutt          #+#    #+#             */
/* Updated: 2026/02/07 14:45:00 by slimvutt         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "philosopher.h"

static void	*one_philo_routine(t_philosopher *p)
{
	pthread_mutex_lock(p->left_fork);
	safe_print(p, "has taken a fork");
	general_usleep(p->shared->time_to_die, p->shared);
	pthread_mutex_unlock(p->left_fork);
	while (!is_stop(p->shared))
		usleep(1000);
	return (NULL);
}

static void	philo_sleep_think(t_philosopher *p)
{
	safe_print(p, "is sleeping");
	general_usleep(p->shared->time_to_sleep, p->shared);
	if (is_stop(p->shared))
		return ;
	safe_print(p, "is thinking");
	if (p->shared->num_philos % 2 != 0)
		general_usleep(p->shared->time_to_eat / 2, p->shared);
}

void	*routine(void *arg)
{
	t_philosopher	*p;

	p = (t_philosopher *)arg;
	if (p->shared->num_philos == 1)
		return (one_philo_routine(p));
	pthread_mutex_lock(&p->shared->meal_mutex);
	p->last_meal = get_time_ms();
	pthread_mutex_unlock(&p->shared->meal_mutex);
	if (p->id % 2 == 0)
		general_usleep(p->shared->time_to_eat / 10, p->shared);
	while (!is_stop(p->shared))
	{
		eat(p);
		if (is_stop(p->shared))
			break ;
		philo_sleep_think(p);
	}
	return (NULL);
}

static int	check_death(t_philosopher *p, int *finished)
{
	size_t	time;

	pthread_mutex_lock(&p->shared->meal_mutex);
	time = get_time_ms();
	if (time - p->last_meal >= p->shared->time_to_die)
	{
		pthread_mutex_lock(&p->shared->print_mutex);
		mornitor_stop(p->shared);
		printf("%zu %d died\n", time - p->shared->time_start, p->id);
		pthread_mutex_unlock(&p->shared->print_mutex);
		pthread_mutex_unlock(&p->shared->meal_mutex);
		return (1);
	}
	if (p->shared->must_eat != -1 && p->eat_count >= p->shared->must_eat)
		*finished += 1;
	pthread_mutex_unlock(&p->shared->meal_mutex);
	return (0);
}

void	*mornitor_routine(void *arg)
{
	t_philosopher	*p;
	int				i;
	int				finished;

	p = (t_philosopher *)arg;
	while (!is_stop(p[0].shared))
	{
		i = -1;
		finished = 0;
		while (++i < p[0].shared->num_philos)
		{
			if (check_death(&p[i], &finished))
				return (NULL);
		}
		if (p[0].shared->must_eat != -1
			&& finished == p[0].shared->num_philos)
		{
			mornitor_stop(p[0].shared);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
