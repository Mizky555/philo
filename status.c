/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsirirak <tsirirak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:06:00 by tsirirak          #+#    #+#             */
/*   Updated: 2023/04/17 02:07:40 by tsirirak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*status_philo(void *input)
{
	t_main	*m;

	m = (t_main *)input;
	if (is_one_philo(m) == 1)
		return (0);
	m->start = time_milli();
	m->after_eat_time = m->start;
	while (1)
	{
		if (pickup_fork_to_eat(m) == 1)
			return (0);
		m->after_eat_time = time_milli();
		m->meals++;
		pthread_mutex_unlock(&m->fork_r);
		pthread_mutex_unlock(m->l_fork);
		if (m->meals == m->must_eat && !(m->full++))
			return (0);
		ft_print(m, 4);
		if (is_philo_dead(m, m->time_sleep) == 1)
			return (0);
		ft_print(m, 5);
	}
	return (0);
}

int	is_one_philo(t_main *m)
{
	if (m->number == 1)
	{
		printf("%d ms, %d has taken a fork_r\n", 0, m->name);
		usleep(m->time_die * 1000);
		printf("%d ms, %d is die\n", m->time_die, m->name);
		m->mod = 1;
		return (1);
	}
	return (0);
}

int	pickup_fork_to_eat(t_main *m)
{
	pthread_mutex_lock(&m->fork_r);
	ft_print(m, 1);
	pthread_mutex_lock(m->l_fork);
	ft_print(m, 2);
	ft_print(m, 3);
	return (is_philo_dead(m, m->time_eat));
}

int	is_philo_dead(t_main *m, int activity)
{
	long	remain_life;

	remain_life = ((m->time_die) - (time_milli() - m->after_eat_time));
	if ((remain_life - activity) <= 0)
	{
		if (remain_life < 0)
			remain_life = remain_life * -1;
		usleep ((remain_life) * 1000);
		m->mod = 1;
		pthread_mutex_lock(m->print);
		printf("%ld ms, %d is die\n", time_milli() - m->start, m->name);
		return (1);
	}
	usleep (activity * 1000);
	return (0);
}

void	ft_print(t_main *m, int mode_print)
{
	pthread_mutex_lock(m->print);
	if (mode_print == 1)
		printf("%ld ms, %d has taken a fork_r\n", \
			time_milli() - m->start, m->name);
	else if (mode_print == 2)
		printf("%ld ms, %d has taken a l_fork\n", \
			time_milli() - m->start, m->name);
	else if (mode_print == 3)
		printf("%ld ms, %d is eating\n", time_milli() - m->start, m->name);
	else if (mode_print == 4)
		printf("%ld ms, %d is sleeping\n", time_milli() - m->start, m->name);
	else if (mode_print == 5)
		printf("%ld ms, %d is thinking\n", time_milli() - m->start, m->name);
	pthread_mutex_unlock(m->print);
}
