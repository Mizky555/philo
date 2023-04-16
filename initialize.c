/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsirirak <tsirirak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:04:11 by tsirirak          #+#    #+#             */
/*   Updated: 2023/04/17 02:05:18 by tsirirak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_main	*initialize_philo(t_main *m, int argc, char **argv)
{
	int	i;

	i = 1;
	m = malloc(sizeof(t_main) * ft_atoi(argv[1]));
	pthread_mutex_init(&m[0].fork_r, NULL);
	while (i <= ft_atoi(argv[1]))
	{
		initial_value(m, i, argc, argv);
		i++;
	}
	i = 0;
	pthread_mutex_init(&m->print2, NULL);
	while (i < m[0].number)
	{
		m[i].print = &m->print2;
		i++;
	}
	return (m);
}

void	initial_value(t_main *m, int i, int argc, char **argv)
{
	if (i == ft_atoi(argv[1]))
		m[i - 1].l_fork = &m[0].fork_r;
	else
	{
		pthread_mutex_init(&m[i].fork_r, NULL);
		m[i - 1].l_fork = &m[i].fork_r;
	}
	m[i - 1].number = ft_atoi(argv[1]);
	m[i - 1].time_die = ft_atoi(argv[2]);
	m[i - 1].time_eat = ft_atoi(argv[3]);
	m[i - 1].time_sleep = ft_atoi(argv[4]);
	m[i - 1].meals = 0;
	m[i - 1].name = i;
	m[i - 1].full = 0;
	m[i - 1].after_eat_time = 0;
	m[i - 1].mod = 0;
	m[i - 1].argc = argc;
	m[i - 1].start = 0;
	if (argc == 6)
		m[i - 1].must_eat = ft_atoi(argv[5]);
	else if (argc == 5)
		m[i - 1].must_eat = 0;
}
