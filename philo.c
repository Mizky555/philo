#include "philo.h"

void initialize_main(t_main **p, int argc, char **argv) //แปลว่าเริ่มต้น ให้ค่า
{
    p->number = ft_atoi(argv[1]);
    p->time_die = ft_atoi(argv[2]);
    p->time_eat = ft_atoi(argv[3]);
    p->time_sleep = ft_atoi(argv[4]);
}


void initialize_philo(t_main *m, t_philo **p) //แปลว่าเริ่มต้น ให้ค่า
{
    i = 1;
    *p = malloc(sizeof(t_philo) * m->number);
    while (i <= p->number)
    {
        p->m = m;
        i++;
    }
}


void    *simu_tread2(void *put)
{
    t_main *tmp;

    tmp = (t_main *)put;
    printf("index = %d\n",tmp->index);
    printf("%d has taken a fork\n",tmp->name[tmp->index]);
    printf("%d is eating\n",tmp->name[tmp->index]);
    printf("%d is sleeping\n",tmp->name[tmp->index]);
    printf("%d is thinking\n",tmp->name[tmp->index]);
}

void    simulation_4(t_main *p)
{
    int index;
    pthread_t t1,t2;
    
    index = 
    while (index >= 2)//philo die
    {
        while (index)
        pthread_create(&t2, NULL, &simu_tread2, (void *)p);
    
        p->index++;
        index++;
        sleep(1);

    }
    printf("is died\n");
}

int main(int argc, char **argv)
{
    t_main  m; // t_main *p -> ต้อง malloc (สามารถสร้างหลายชิ้นได้)
    t_philo *p;
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
    initialize_main(&p, argc, argv);
    initialize_philo(&m, &p);
    if (argc == 5)
        simulation_4(&p);
    // else if (argc == 6)
    //     simulation_5();
}