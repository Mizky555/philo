#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_main
{
    int number;
    int time_die;
    int time_eat;
    int time_sleep;
    int must_eat;
    int meals;
    int name;
    int fork;
    long after_eat_time;
    int mod;
    pthread_t philo;
    pthread_mutex_t *print;
    pthread_mutex_t print2;
    pthread_mutex_t fork_r;
    pthread_mutex_t *l_fork; //ต้องเก็บส้อมของคนข้างๆ เลยต้องเป๋น Pointer(ต้องชี้เพื่อหยิบ)



}   t_main;






int check_digit(char **argv);
int ft_atoi(const char *str);

#endif
