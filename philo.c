/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsirirak <tsirirak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 01:47:22 by tsirirak          #+#    #+#             */
/*   Updated: 2023/04/17 01:47:22 by tsirirak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_main	*m;
	int		i;

	if (argc != 5 && argc != 6)
	{
		printf("Error argc\n");
		return (0);
	}
	if (check_digit(argv) == 0)
	{
		printf("Error is not digit\n");
		return (0);
	}
	if (argc == 6 && ft_atoi(argv[5]) == 0)
	{
		return (0);
	}
	m = initialize_philo(m, argc, argv);
	simulation(m);
	ft_free_all(m);
}

long	time_milli(void)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	return (((time_now.tv_sec * 1000) + (time_now.tv_usec / 1000)));
}

void	check_end(t_main *m)
{
	int	i;
	int	j;
	int	philo_full;

	i = 0;
	while (1)
	{
		if (m[i % (m->number)].mod == 1)
			break ;
		if (m->argc == 6)
		{
			j = 0;
			philo_full = 0;
			while (j < m->number)
			{
				if (m[j].full == 1)
					philo_full++;
				j++;
			}
			if (philo_full == m->number)
				break ;
			i++;
		}
	}
}

void	simulation(t_main *m)
{
	int	i;

	i = 1;
	while (i <= m[0].number)
	{
		if (m[i - 1].name % 2 != 0)
			pthread_create(&m[i - 1].philo, NULL, \
				&status_philo, (void *)&m[i - 1]);
		i++;
	}
	i = 1;
	usleep(100);
	while (i <= m[0].number)
	{
		if (m[i - 1].name % 2 == 0)
			pthread_create(&m[i - 1].philo, NULL, \
				&status_philo, (void *)&m[i - 1]);
		i++;
	}
	check_end(m);
}

void	ft_free_all(t_main *m)
{
	int	i;

	pthread_mutex_destroy(&m->print2);
	i = 0;
	while (i < m[0].number)
		pthread_mutex_destroy(&m[i++].fork_r);
	i = 0;
	while (i < m[0].number)
		pthread_detach(m[i++].philo);
	free(m);
}
