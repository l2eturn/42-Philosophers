/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 01:33:10 by slimvutt          #+#    #+#             */
/*   Updated: 2025/12/21 01:33:10 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include "utils.h"


int main(int ac, char **av)
{
	pthread_t			*philos;
	pthread_mutex_t		*forks;
	t_shared			shared;
	int					numb_philos;

	numb_philos = (int)ft_atoi(av[1]);
	philos = malloc(sizeof(pthread_t) * numb_philos);
	forks = malloc(sizeof(pthread_mutex_t) * numb_philos);

}
