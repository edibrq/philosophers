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

int	main(int argc, char **argv)
{
	t_state	state;
	int		i;

	if (parse_args(&state, argc, argv) != 0)
		return (1);
	if (init(&state) != 0)
		return (1);
	i = init_forks(&state);
	if (i)
	{
		m_free(&state, i, 0);
		return (1);
	}
	i = simulation(&state);
	if (i)
	{
		m_free(&state, 0, i);
		return (1);
	}
	m_free(&state, 5, 5);
	return (0);
}
