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

void	*kill_philo(t_state *state, t_philo *philo)
{
	state->someone_dead = 1;
	philo->exitcode = 1;
	print_log(state, philo, 4);
	return (NULL);
}

static void	*death(void *args)
{
	t_philo			*philo;
	t_state			*state;
	struct timeval	tvx;
	int				sum;

	state = args;
	while (1)
	{
		sum = 0;
		philo = state->nth_philo;
		while (philo)
		{
			gettimeofday(&tvx, NULL);
			philo->tsmp_msec = (tvx.tv_usec / 1000) + (tvx.tv_sec * 1000)
				- state->t_start;
			if (philo->tsmp_msec - philo->tsmp_lastmeal >= state->t_die)
				return (kill_philo(state, philo));
			sum += philo->ate_enough;
			if (sum == state->n_philos)
				return (NULL);
			philo = philo->prev;
		}
		usleep(1000);
	}
}

static int	join_philos(t_state *state)
{
	t_philo	*philo;

	philo = state->nth_philo;
	while (philo)
	{
		if (pthread_join(philo->philo_thread, NULL))
			return (-1);
		philo = philo->prev;
	}
	return (0);
}

int	simulation(t_state *state)
{
	int	i;
	int	error;

	i = 0;
	while (i < state->n_philos)
	{
		error = philo(state, i + 1);
		if (error)
			return (error);
		i++;
	}
	if (pthread_create(&state->death, NULL, &death, state))
	{
		printf("(Error) Can't create death thread\n");
		return (-1);
	}
	state->all_philos_created = 1;
	if (pthread_join(state->death, NULL) || join_philos(state))
	{
		printf("(Error) Can't join threads\n");
		return (-1);
	}
	return (0);
}
