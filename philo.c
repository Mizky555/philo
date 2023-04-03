#include "philo.h"

int check_digit(char **argv)
{
    int i = 1;
    int j = 0;

    while (argv[i]) 
    {
        j = 0;
        while (argv[i][j])
        {
            if (argv[i][j] < '0' || argv[i][j] > '9')
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

void initialize_philo(t_philo *p, int argc, char **argv) //แปลว่าเริ่มต้น ให้ค่า
{
    int i;

    i = 0;
    p->number = ft_atoi(argv[1]);
    p->time_die = ft_atoi(argv[2]);
    p->time_eat = ft_atoi(argv[3]);
    p->time_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        p->must_eat = ft_atoi(argv[5]);
    p->name = (int *)malloc(sizeof(int) * (p->number));
    while (i < p->number)
    {
        // printf("i = %d\n", i);
        p->name[i] = i + 1;
        i++;
    }
    p->index = 0;
}


void    *simu_tread2(void *put)
{
    t_philo *tmp;

    tmp = (t_philo *)put;
    printf("index = %d\n",tmp->index);
    printf("%d has taken a fork\n",tmp->name[tmp->index]);
    printf("%d is eating\n",tmp->name[tmp->index]);
    printf("%d is sleeping\n",tmp->name[tmp->index]);
    printf("%d is thinking\n",tmp->name[tmp->index]);
}

void    simulation_4(t_philo *p)
{
    int index;
    pthread_t t1,t2;
    
    index = 1;
    while (index <= 2)//philo die
    {

        pthread_create(&t2, NULL, &simu_tread2, (void *)p);
        // p->index++;
        index++;
        sleep(1);

    }
    printf("is died\n");
}

int main(int argc, char **argv)
{
    t_philo p;
    if (argc != 5 && argc != 6)
    {   
    printf("argc %d\n", argc);
        printf("Error argc\n");
        return (0);
    }
    if (check_digit(argv) == 0)
    {
        printf("Error is not digit\n");
        return (0);
    }
    initialize_philo(&p, argc, argv);
    if (argc == 5)
        simulation_4(&p);
    // else if (argc == 6)
    //     simulation_5();
}