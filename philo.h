#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_main
{
    int number;
    int time_die;
    int time_eat;
    int time_sleep;
    int must_eat;
    int name;
    int fork;
    pthread_t philo;
    pthread_mutex_t fork_r;
    pthread_mutex_t *l_fork;
    
}   t_main;






int check_digit(char **argv);
int ft_atoi(const char *str);

#endif