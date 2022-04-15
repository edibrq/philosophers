/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chiram <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 17:51:09 by chiram            #+#    #+#             */
/*   Updated: 2021/11/11 13:45:27 by chiram           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init(t_state *state)
{
	struct timeval	tvx;

	if (gettimeofday(&tvx, NULL))
	{
		printf("(Error) Can't measure time");
		return (1);
	}
	state->t_start = (tvx.tv_usec / 1000) + (tvx.tv_sec * 1000);
	state->nth_philo = NULL;
	if (pthread_mutex_init(&state->print_mutex, NULL))
	{
		printf("(Error) Mutex is not initialised");
		return (1);
	}
	state->someone_dead = 0;
	state->all_philos_created = 0;
	if (state->n_philos < 150)
		state->sleep_interval = 100;
	else
		state->sleep_interval = 500;
	return (0);
}

int	init_forks(t_state *state)
{
	int	i;

	state->forks = malloc(sizeof(pthread_mutex_t) * state->n_philos);
	if (!state->forks)
		return (1);
	i = 0;
	while (i < state->n_philos)
	{
		if (pthread_mutex_init(&state->forks[i], NULL) != 0)
		{
			printf("(Error) Can't create mutex for forks\n");
			return (i);
		}
		i++;
	}
	return (0);
}
