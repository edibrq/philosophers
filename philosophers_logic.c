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

static t_philo	*new_philo(t_state *state, int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->ph_vars = state;
	philo->id = id;
	philo->ate_enough = 0;
	philo->tsmp_lastmeal = 0;
	philo->times_eaten = 0;
	philo->tsmp_msec = 0;
	philo->prev = state->nth_philo;
	state->nth_philo = philo;
	philo->exitcode = 0;
	if (philo->id < state->n_philos)
		philo->right_fork = &state->forks[philo->id];
	else
		philo->right_fork = &state->forks[0];
	philo->left_fork = &state->forks[philo->id - 1];
	return (philo);
}

static void	eat(t_state *state, t_philo *philo)
{
	print_log(state, philo, 1);
	philo->tsmp_lastmeal = philo->tsmp_msec;
	msleep(state->t_eat, state->sleep_interval);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->times_eaten++;
	if (philo->times_eaten == state->n_must_eat)
	{
		philo->ate_enough = 1;
		return ;
	}
	print_log(state, philo, 2);
	msleep(state->t_sleep, state->sleep_interval);
}

static void	cycle(t_state *state, t_philo *philo)
{
	if (philo->times_eaten)
		print_log(state, philo, 3);
	if (philo->left_fork == philo->right_fork)
		return ;
	pthread_mutex_lock(philo->left_fork);
	print_log(state, philo, 0);
	pthread_mutex_lock(philo->right_fork);
	print_log(state, philo, 0);
	eat(state, philo);
	usleep(50);
}

static void	*lifecycle(void *args)
{
	t_philo	*philo;
	t_state	*state;

	philo = args;
	state = philo->ph_vars;
	while (!(state->all_philos_created))
		usleep(5);
	if (!(philo->id % 2))
		msleep(state->t_eat - 1, state->sleep_interval);
	while (1)
	{
		if (state->someone_dead)
			break ;
		cycle(state, philo);
		if (philo->exitcode || philo->ate_enough)
			break ;
	}
	return (NULL);
}

int	philo(t_state *state, int id)
{
	t_philo	*philo;

	philo = new_philo(state, id);
	if (!philo)
		return (id);
	if (pthread_create(&philo->philo_thread, NULL, &lifecycle, (void *)philo))
	{
		printf("(Error) Philo's thread can't be created\n");
		return (id);
	}
	return (0);
}
