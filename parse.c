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

static bool	is_numeric_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}

static bool	is_overflowed_str(char *s)
{
	long long	n;

	if (ft_strlen(s) > 11)
		return (true);
	n = ft_atoi(s);
	if (n > INT_MAX || n < INT_MIN)
		return (true);
	return (false);
}

static bool	is_valid(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_numeric_str(argv[i]))
		{
			printf("(Error) Passed args is not numeric or negative");
			return (false);
		}
		if (is_overflowed_str(argv[i]))
		{
			printf("(Error) Passed args is not in int range");
			return (false);
		}
		if (ft_atoi(argv[i]) < 0)
		{
			printf("(Error) Passed args are not positive");
			return (false);
		}
		i++;
	}
	return (true);
}

int	parse_args(t_state *arg, int argc, char **argv)
{
	if (!(argc == 5 || argc == 6))
	{
		printf("(Error) Invalid number of args were passed\n");
		return (1);
	}
	if (!is_valid(argv))
		return (1);
	arg->n_philos = ft_atoi(argv[1]);
	if (arg->n_philos == 0)
	{
		printf("Bad number of philos\n");
		return (-1);
	}
	arg->t_die = ft_atoi(argv[2]);
	arg->t_eat = ft_atoi(argv[3]);
	arg->t_sleep = ft_atoi(argv[4]);
	arg->n_must_eat = -1;
	if (argv[5])
		arg->n_must_eat = ft_atoi(argv[5]);
	return (0);
}
