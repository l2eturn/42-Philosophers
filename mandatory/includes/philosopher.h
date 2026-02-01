/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 22:58:29 by slimvutt          #+#    #+#             */
/*   Updated: 2025/12/20 22:58:29 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
//# define MAX_PHILOSOPHERS 67
//# define MAX_FORKS		67
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_philosopher
{
	int				id;
	int				eat_count;
	size_t			last_meal;

	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;

	pthread_t		thread;

	t_shared		*shared;
}				t_philosopher;

typedef struct s_shared
{
	int				num_philos;
	int				must_eat;
	int				stop;

	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;

	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;

	t_philosopher	*philos;
}				t_shared;

#endif
