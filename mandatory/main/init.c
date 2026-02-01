/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slimvutt <slimvut@fpgij;dgj;ds.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 05:20:14 by slimvutt          #+#    #+#             */
/*   Updated: 2025/12/21 05:20:14 by slimvutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "philosopher.h"
#include "utils.h"

void	init_shared(t_shared *shared, pthread_mutex_t *forks, int ac, char **av)
{
	int					numb_philos;

	numb_philos = (int)ft_atoi(av[1]);
	shared->num_philos = numb_philos;
	shared->forks = forks;
}

