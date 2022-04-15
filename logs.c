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

int	msleep(long sleep, int interval)
{
	struct timeval	tvx;
	long			start_time;
	long			atm;
	long			to_sleep;

	gettimeofday(&tvx, NULL);
	start_time = (tvx.tv_usec / 1000) + (tvx.tv_sec * 1000);
	atm = start_time;
	to_sleep = start_time + sleep;
	while (atm < to_sleep)
	{
		usleep(interval);
		gettimeofday(&tvx, NULL);
		atm = (tvx.tv_usec / 1000) + (tvx.tv_sec * 1000);
	}
	return (0);
}

void	print_log(t_state *state, t_philo *philo, int i)
{
	char			*message[5];
	struct timeval	tvx;

	message[0] = "has taken fork";
	message[1] = "is eating";
	message[2] = "is sleeping";
	message[3] = "is thinking";
	message[4] = "died";
	pthread_mutex_lock(&state->print_mutex);
	gettimeofday(&tvx, NULL);
	philo->tsmp_msec = ((tvx.tv_usec / 1000)
			+ (tvx.tv_sec * 1000)) - state->t_start;
	if (i != 4 && !state->someone_dead && !philo->ate_enough)
		printf("%ld %d %s\n", philo->tsmp_msec, philo->id, message[i]);
	if (i == 4 && !philo->ate_enough)
		printf("%ld %d %s\n", ((tvx.tv_usec / 1000)
				+ (tvx.tv_sec * 1000)) - state->t_start, philo->id, message[i]);
	pthread_mutex_unlock(&state->print_mutex);
}
