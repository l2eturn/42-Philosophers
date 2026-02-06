/* ************************************************************************** */
/*				*/
/*				:::				  ::::::::   */
/*   philo.h				:+:				  :+:				:+:   */
/*				+:+ +:+				 +:+				 */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>				+#+  +:+				   +#+				*/
/*				+#+#+#+#+#+   +#+				   */
/*   Created: 2025/12/20 22:58:29 by slimvutt				  #+#				#+#				 */
/*   Updated: 2025/12/20 22:58:29 by slimvutt				 ###   ########.fr				   */
/*				*/
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
# include <limits.h>

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

// --- init.c ---
void				shared_time_init(int ac, char **av, t_shared *shared);
int					shared_mutex_init(t_shared *shared);
void				forks_init(t_shared *shared, pthread_mutex_t *forks, int n);
void				philos_init(t_philosopher *p, t_shared *shared, int n);
int				philos_create_threads(t_philosopher *p, int n);

// --- routines.c ---
void				*routine(void *arg);
void				*mornitor_routine(void *arg);

// --- actions.c ---
void				eat(t_philosopher *p);
void				take_forks(t_philosopher *p);
void				put_forks(t_philosopher *p);

// --- helpers.c ---
size_t				get_time_ms(void);
void				general_usleep(size_t ms, t_shared *shared);
void				safe_print(t_philosopher *p, char *str);
int					is_stop(t_shared *shared);
void				mornitor_stop(t_shared *shared);

size_t				ft_atoi(char *str);
void				error_message(char *text, int signal);
int					ft_isdigit(char c);
int					ft_strlen(char *str);
#endif
