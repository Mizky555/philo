#include "philo.h"


t_main *initialize_philo(t_main *m, int argc, char **argv) //แปลว่าเริ่มต้น ให้ค่า(การเตรียมข้อมูล)
{
    int     i;

    i = 1;
    m = malloc(sizeof(t_main) * ft_atoi(argv[1]));

    while (i <= ft_atoi(argv[1]))
    {
        m[i - 1].number = ft_atoi(argv[1]);
        m[i - 1].time_die = ft_atoi(argv[2]);
        m[i - 1].time_eat = ft_atoi(argv[3]);
        m[i - 1].time_sleep = ft_atoi(argv[4]);
        if (argc == 6)
            m[i - 1].must_eat = ft_atoi(argv[5]);
        else if (argc == 5)
            m[i - 1].must_eat = 0;
        m[i - 1].name = i;
        i++;
    }
    return (m);
}


void    *simu_tread2(void *input)
{
    t_main *m;

    m = (t_main *)input;
    while (1)
    {
    printf("%d has taken a fork\n",m->name);
    printf("%d is eating\n",m->name);
    printf("%d is sleeping\n",m->name);
    printf("%d is thinking\n",m->name);}
}

void    simulation_4(t_main *m)
{   
    int i = 1;
    while (i <= m[0].number)
    {
        pthread_create(&m[i - 1].philo, NULL, &simu_tread2, (void *)&m[i - 1]);
        i++;
    }
    i = 1;
    while (i <= m[0].number)
    {
        pthread_join(m[i - 1].philo,NULL);
        i++;
    }
    printf("is died\n");
}

int main(int argc, char **argv)
{
    t_main  *m; // t_main *p -> ต้อง malloc (สามารถสร้างหลายชิ้นได้)
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
    m = initialize_philo(m, argc, argv);
    if (argc == 5 || argc == 6)
        simulation_4(m);
    

}

//พรุง่นี้ทำให้ฟิโลตาย