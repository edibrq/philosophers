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

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_philo
{
	int					id;
	int					ate_enough;
	long				tsmp_msec;
	int					exitcode;
	long				tsmp_lastmeal;
	int					times_eaten;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	void				*ph_vars;
	struct s_philo		*prev;
	pthread_t			philo_thread;
}	t_philo;

typedef struct s_state
{
	long				n_philos;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	long				n_must_eat;
	long				t_start;
	pthread_mutex_t		print_mutex;
	int					someone_dead;
	int					sleep_interval;
	int					all_philos_created;
	t_philo				*nth_philo;
	pthread_mutex_t		*forks;
	pthread_t			death;
}	t_state;

long long	ft_atoi(const char *str);
void		print_log(t_state *state, t_philo *philo, int n);
int			msleep(long sleep, int inter);
void		*kill_philo(t_state *state, t_philo *philo);
int			parse_args(t_state *arg, int argc, char **argv);
int			init(t_state *state);
int			philo(t_state *state, int id);
int			init_forks(t_state *state);
int			simulation(t_state *state);
void		m_free(t_state *state, int forks, int philos);
int			ft_strlen(char *s);

#endif
