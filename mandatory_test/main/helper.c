/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 23:55:07 by slimvutt          #+#    #+#             */
/*   Updated: 2026/02/06 23:55:07 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	mornitor_stop(t_shared *s)
{
	pthread_mutex_lock(&s->stop_mutex);
	s->stop = 1;
	pthread_mutex_unlock(&s->stop_mutex);
}

size_t get_time_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	general_usleep(size_t gen_time, t_shared *s)
{
	size_t	start;

	start = get_time_ms();
	while (!is_stop(s))
	{
		if (get_time_ms() - start >= gen_time)
			break;
		usleep(1000);
	}
}

void	safe_print(t_philosopher *p, char *msg)
{
	size_t time;

	pthread_mutex_lock(&p->shared->print_mutex);
	time = get_time_ms() - p->shared->time_start;
	if (!is_stop(p->shared))
		printf("%zu %d %s\n", time, p->id, msg);
	pthread_mutex_unlock(&p->shared->print_mutex);
}

int	is_stop(t_shared *shared)
{
	int	ret;

	pthread_mutex_lock(&shared->stop_mutex);
	ret = shared->stop;
	pthread_mutex_unlock(&shared->stop_mutex);
	return	(ret);
}