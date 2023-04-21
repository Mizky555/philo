/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsirirak <tsirirak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 02:01:40 by tsirirak          #+#    #+#             */
/*   Updated: 2023/04/17 02:01:40 by tsirirak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_main
{
	int				number;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				meals;
	int				name;
	int				full;
	long			after_eat_time;
	int				mod;
	int				argc;
	long			start;
	pthread_t		philo;
	pthread_mutex_t	*print;
	pthread_mutex_t	print2;
	pthread_mutex_t	fork_r;
	pthread_mutex_t	*l_fork;
}	t_main;

int		sleep_to_eat(t_main *m);
void	ft_print(t_main *m, int mode_print);
int		check_digit(char **argv);
int		ft_atoi(const char *str);
void	ft_free_all(t_main *m);
void	simulation(t_main *m);
void	check_end(t_main *m);
long	time_milli(void);
t_main	*initialize_philo(t_main *m, int argc, char **argv);
void	initial_value(t_main *m, int i, int argc, char **argv);
void	*status_philo(void *input);
int		is_one_philo(t_main *m);
int		pickup_fork_to_eat(t_main *m);
int		is_philo_dead(t_main *m, int activity);

#endif
