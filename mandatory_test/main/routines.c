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

//void	*routine(void *arg)
//{
//	t_philosopher   *p;

//	p = arg;

//	if (p->shared->num_philos == 1)
//	{
//		pthread_mutex_lock(p->left_fork);
//		safe_print(p, "has taken a fork");
//		general_usleep(p->shared->time_to_die, p->shared); 
//		pthread_mutex_unlock(p->left_fork);
//		while (!is_stop(p->shared))
//			usleep(1000); 
//		return (NULL);
//	}
//	pthread_mutex_lock(&p->shared->meal_mutex);
//	p->last_meal = get_time_ms();
//	pthread_mutex_unlock(&p->shared->meal_mutex);
//	if (p->id % 2 == 0)
//		usleep(1000);
//	while (!is_stop(p->shared))
//	{
//		eat(p);
//		if (is_stop(p->shared))
//			break;
//		safe_print(p, "is sleeping");
//		general_usleep(p->shared->time_to_sleep, p->shared);
//		if (is_stop(p->shared))
//			break;
//		safe_print(p, "is thinking");
//		if (p->shared->num_philos % 2 != 0) 
//			usleep(1000);
//	}
//	return (NULL);
//}

//void    *mornitor_routine(void *arg)
//{
//    t_philosopher	*p;
//    int				i;
//    int				finished_eating;
//    size_t			time_now;

//	p = (t_philosopher *)arg;
//	while (!is_stop(p[0].shared))
//	{
//		i = 0;
//		finished_eating = 0;
//		while (i < p[0].shared->num_philos)
//		{
//			pthread_mutex_lock(&p[i].shared->meal_mutex);
//			time_now = get_time_ms();
//			if (time_now - p[i].last_meal >= p[i].shared->time_to_die)
//			{
//				pthread_mutex_lock(&p[i].shared->print_mutex);
//				printf("%zu %d died\n", time_now - p[i].shared->time_start, p[i].id);
//				pthread_mutex_unlock(&p[i].shared->print_mutex);
//				mornitor_stop(p[i].shared);
//				pthread_mutex_unlock(&p[i].shared->meal_mutex);
//				return (NULL);
//			}
//			if (p[i].shared->must_eat != -1 && p[i].eat_count >= p[i].shared->must_eat)
//				finished_eating++;
//			pthread_mutex_unlock(&p[i].shared->meal_mutex);
//			i++;
//		}
//		if (p[0].shared->must_eat != -1 && finished_eating == p[0].shared->num_philos)
//		{
//			mornitor_stop(p[0].shared);
//			return (NULL);
//		}
//		usleep(1000);
//	}
//	return (NULL);
//}

static void	*one_philo_routine(t_philosopher *p)
{
	pthread_mutex_lock(p->left_fork);
	safe_print(p, "has taken a fork");
	general_usleep(p->shared->time_to_die, p->shared);
	pthread_mutex_unlock(p->left_fork);
	return (NULL);
}

static int	check_dead(t_philosopher *p)
{
	size_t	curr;

	pthread_mutex_lock(&p->shared->meal_mutex);
	curr = get_time_ms();
	if (curr - p->last_meal >= p->shared->time_to_die)
	{
		pthread_mutex_unlock(&p->shared->meal_mutex);
		mornitor_stop(p->shared);
		pthread_mutex_lock(&p->shared->print_mutex);
		printf("%zu %d died\n", curr - p->shared->time_start, p->id);
		pthread_mutex_unlock(&p->shared->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&p->shared->meal_mutex);
	return (0);
}

static int	check_all_ate(t_philosopher *p)
{
	int	i;
	int	finished;

	if (p[0].shared->must_eat == -1)
		return (0);
	i = -1;
	finished = 0;
	while (++i < p[0].shared->num_philos)
	{
		pthread_mutex_lock(&p[i].shared->meal_mutex);
		if (p[i].eat_count >= p[0].shared->must_eat)
			finished++;
		pthread_mutex_unlock(&p[i].shared->meal_mutex);
	}
	if (finished == p[0].shared->num_philos)
	{
		mornitor_stop(p[0].shared);
		return (1);
	}
	return (0);
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
		safe_print(p, "is sleeping");
		general_usleep(p->shared->time_to_sleep, p->shared);
		safe_print(p, "is thinking");
		if (p->shared->num_philos % 2 != 0)
			usleep(1000);
	}
	return (NULL);
}

void	*mornitor_routine(void *arg)
{
	t_philosopher	*p;
	int				i;

	p = (t_philosopher *)arg;
	while (!is_stop(p[0].shared))
	{
		i = -1;
		while (++i < p[0].shared->num_philos)
		{
			if (check_dead(&p[i]))
				return (NULL);
		}
		if (check_all_ate(p))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
