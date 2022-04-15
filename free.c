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

static void	free_forks(t_state *state, int n)
{
	int	i;

	i = 0;
	if (n == 5)
		n = state->n_philos;
	while (i < n)
	{
		pthread_mutex_destroy(&state->forks[i]);
		i++;
	}
	if (state->forks)
		free(state->forks);
}

static void	free_philos(t_state *state, int n)
{
	t_philo	*curr;
	t_philo	*t;
	int		i;

	i = 0;
	if (n == 5)
		n = state->n_philos;
	curr = state->nth_philo;
	while (i < n)
	{
		t = curr;
		curr = curr->prev;
		free(t);
		i++;
	}
}

void	m_free(t_state *state, int forks, int philos)
{
	if (forks)
		free_forks(state, forks);
	if (philos)
		free_philos(state, philos);
	pthread_mutex_destroy(&state->print_mutex);
}
