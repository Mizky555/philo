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
}   t_main;

typedef struct s_philo
{
    int must_eat;
    int *name;
    int index;
    t_main  *m;
    
}   t_philo;




int ft_atoi(const char *str);

#endif