/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 03:05:25 by slimvutt          #+#    #+#             */
/*   Updated: 2025/12/21 03:05:25 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include "utils.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len ++;
	return (len);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

size_t	ft_atoi(char *str)
{
	int		sign;
	size_t	res;
	int		i;

	sign = 1;
	res = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i ++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i ++;
	}
	while (ft_isdigit(str[i]) && str[i])
	{
		res = res * 10 + (str[i] - '0');
		i ++;
	}
	return ((sign) * (res));
}

void	error_message(char *text, int signal)
{
	if (text)
		write(2, text, ft_strlen(text) + 1);
	exit(signal);
}

//int philos_init(t_shared *s, t_philo **philos)
//{
//	int i = 0;

//	*philos = malloc(sizeof(t_philo) * s->num_philos);
//	if (!*philos)
//		return (1);

//	while (i < s->num_philos)
//	{
//		if (pthread_mutex_init(&(*philos)[i].meal_mutex, NULL) != 0)
//		{
//			while (--i >= 0)
//				pthread_mutex_destroy(&(*philos)[i].meal_mutex);
//			free(*philos);
//			return (1);
//		}
//		i++;
//	}
//	return (0);
//}