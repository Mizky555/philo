#include "philo.h"

int time_milli(int time_start)
{
    struct timeval time_now;


    gettimeofday(&time_now, NULL);
    return (((time_now.tv_sec * 1000) + (time_now.tv_usec / 1000)) - time_start);
}


t_main *initialize_philo(t_main *m, int argc, char **argv) //แปลว่าเริ่มต้น ให้ค่า(การเตรียมข้อมูล)
{
    int     i;

    i = 1;
    m = malloc(sizeof(t_main) * ft_atoi(argv[1]));//จองตามจำนวน Philo
    pthread_mutex_init(&m[0].fork_r,NULL); // philo คนที่ 1 (ตัวถัดๆไป บรรทัดที่ 37)

    while (i <= ft_atoi(argv[1]))//วนให้ค่าตามจำนวน Philo
    {
        if (i == ft_atoi(argv[1]))//สำหรับคนสุดท้าย ให้มือซ้ายหยิบส้อม
        {
            m[i - 1].l_fork = &m[0].fork_r;
        }
        else//เริ่มต้นที่คนที่ 2 array[1]
        {
            pthread_mutex_init(&m[i].fork_r,NULL);
            m[i - 1].l_fork = &m[i].fork_r;//คนก่อนหน้าใช้มือซ้าย หยิบส้อมมือขวาของคนปัจจุบัน
        }

        m[i - 1].number = ft_atoi(argv[1]);
        m[i - 1].time_die = ft_atoi(argv[2]);
        m[i - 1].time_eat = ft_atoi(argv[3]);
        m[i - 1].time_sleep = ft_atoi(argv[4]);
        m[i - 1].fork = 1;
        if (argc == 6)
            m[i - 1].must_eat = ft_atoi(argv[5]);
        else if (argc == 5)
            m[i - 1].must_eat = 0;
        m[i - 1].name = i;
        i++;
    }
    // for (int i = 0 ; i < m[0].number ; i++)
    // {
    //     printf("%d fork _r  =  %p\n", i, &m[i].fork_r);
    //     printf("%d l_fork  =  %p\n", i, m[i].l_fork);
    // }
    struct timeval t;
    time_milli(gettimeofday(&t, NULL));
    exit(1);

    return (m);
}



void    *status_philo(void *input)
{
    t_main *m;
    int i = 1;

    m = (t_main *)input;
    while (i)
    {
        // usleep(400);
        // pthread_mutex_lock(&m->fork_r);
        // pthread_mutex_lock(m->l_fork);
        printf("%d has taken a fork\n",m->name);
        printf("%d is eating\n",m->name);
        printf("%d is sleeping\n",m->name);
        printf("%d is thinking\n",m->name);
        // pthread_mutex_unlock(&m->fork_r);
        // pthread_mutex_unlock(m->l_fork);
    }
    return (0);
}

void    simulation(t_main *m)
{
    int i = 1;


    while (i <= m[0].number)
    {

        pthread_create(&m[i - 1].philo, NULL, &status_philo, (void *)&m[i - 1]);//แตกหน่อ
        i++;
    }
    i = 1;
    while (i <= m[0].number)
    {
        pthread_join(m[i - 1].philo,NULL);//รอจนกว่าตัวแรกจะทำงานเสร็จ
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
    m = initialize_philo(m, argc, argv);//กำหนดค่าให้กับ Philo ทุกคน
    simulation(m);//Philo กินนอนคิด จับเวลา


}



//ทำเงื่อนไขการขโมย ft simu ให้ตรงตามโจทย
//ทำเงื่อนไข must_eat philo die
//เวลา กิน นอน อดตาย
