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
# define MAX_PHILOSOPHERS 6464
# define MAX_FORKS		6464
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <stdlib.h>

typedef struct s_shared
{
	int				num_philos;
	int				must_eat;
	int				stop;

	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			time_start;

	pthread_mutex_t	stop_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
}				t_shared;

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

#endif
