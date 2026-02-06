/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 23:54:17 by slimvutt          #+#    #+#             */
/*   Updated: 2026/02/06 23:54:17 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	take_forks(t_philosopher *p)
{
	if ((p->id) % 2 == 1)
	{
		pthread_mutex_lock(p->left_fork);
		safe_print(p, "has taken a fork");
		pthread_mutex_lock(p->right_fork);
		safe_print(p, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(p->right_fork);
		safe_print(p, "has taken a fork");
		pthread_mutex_lock(p->left_fork);
		safe_print(p, "has taken a fork");
	}
}

void	put_forks(t_philosopher *p)
{
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
}

void	eat(t_philosopher *p)
{
	take_forks(p);
	pthread_mutex_lock(&p->shared->meal_mutex);
	p->last_meal = get_time_ms();
	p->eat_count ++;
	pthread_mutex_unlock(&p->shared->meal_mutex);
	safe_print(p, "is eating");
	general_usleep(p->shared->time_to_eat, p->shared);
	put_forks(p);
}
