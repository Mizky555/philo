#include "philo.h"

long time_milli(void)
{
    struct timeval time_now;

    gettimeofday(&time_now, NULL);
    return (((time_now.tv_sec * 1000) + (time_now.tv_usec / 1000)));
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
        m[i - 1].meals = 0;
        m[i - 1].name = i;
        m[i - 1].after_eat_time = 0;
        m[i - 1].mod = 0;
        if (argc == 6)
            m[i - 1].must_eat = ft_atoi(argv[5]);
        else if (argc == 5)
            m[i - 1].must_eat = 0;
        i++;
    }

    i = 0;
    pthread_mutex_init(&m->print2,NULL);
    while (i < m[0].number)
    {
        m[i].print = &m->print2;
        i++;
    }
    return (m);
}


// void    *status_philo(void *input)
// {
//     t_main *m;
//     int i = 1;
//     long    start;

//     m = (t_main *)input;
//     start = time_milli(); //start
//     while (i)
//     {
//         pthread_mutex_lock(&m->fork_r);
//         printf("%ld ms, %d has taken a fork_r\n",time_milli() - start, m->name);
//         pthread_mutex_lock(m->l_fork);
//         printf("%ld ms, %d has taken a l_fork\n",time_milli() - start, m->name);
//         printf("%ld ms, %d is eating\n",time_milli() - start, m->name);//เวลาเริ่มกิน(time_milli คือเวลาจบ -> end - start)
//         usleep(m->time_eat * 1000);//เวลาในการกิน
//         m->meals++;
//         pthread_mutex_unlock(&m->fork_r);
//         pthread_mutex_unlock(m->l_fork);
//         if (m->meals == m->must_eat)//ครบจำนวนการกินทุกตัว = จบ
//             break;
//         printf("%ld ms, %d is sleeping\n",time_milli() - start, m->name);//เวลาเริ่มนอน
//         usleep(m->time_sleep * 1000);//เวลาในการนอน
//         printf("%ld ms, %d is thinking\n",time_milli() - start, m->name);
//     }
//     return (0);
// }

int    is_philo_dead(t_main *m, int activity)
{
    long    remain_life;//เวลาชีวิตที่เหลืออยู่

    remain_life = ((m->time_die) - (time_milli() - m->after_eat_time));

    if ((remain_life - activity) <= 0)
    {
        if (remain_life < 0)
            remain_life = remain_life * -1;
        usleep((remain_life) * 1000);
        return (1);
    }
    usleep(activity * 1000);
    return(0);
}

void    *status_philo(void *input)
{
    t_main *m;
    int i = 1;
    long    start;

    m = (t_main *)input;
    start = time_milli(); //start
    m->after_eat_time = start;



    while (i)
    {
        pthread_mutex_lock(&m->fork_r);
        pthread_mutex_lock(m->print);
        printf("%ld ms, %d has taken a fork_r\n",time_milli() - start, m->name);
        pthread_mutex_unlock(m->print);
        pthread_mutex_lock(m->l_fork);
        pthread_mutex_lock(m->print);
        printf("%ld ms, %d has taken a l_fork\n",time_milli() - start, m->name);
        pthread_mutex_unlock(m->print);
        pthread_mutex_lock(m->print);
        printf("%ld ms, %d is eating\n",time_milli() - start, m->name);
        pthread_mutex_unlock(m->print);

        if (is_philo_dead(m, m->time_eat) == 1)
        {
            pthread_mutex_lock(m->print);
            printf("%ld ms, %d is die\n",time_milli() - start, m->name);
            pthread_mutex_unlock(&m->fork_r);
            pthread_mutex_unlock(m->l_fork);
            m->mod = 1;
            return (0);
        }

        m->after_eat_time = time_milli();
        m->meals++;
        pthread_mutex_unlock(&m->fork_r);
        pthread_mutex_unlock(m->l_fork);

        if (m->meals == m->must_eat)
        {
            m->mod = 2;
            return (0);
        }

        pthread_mutex_lock(m->print);
        printf("%ld ms, %d is sleeping\n", time_milli() - start, m->name);
        pthread_mutex_unlock(m->print);

        if (is_philo_dead(m, m->time_sleep) == 1)
        {
            m->mod = 1;
            pthread_mutex_lock(m->print);
            printf("%ld ms, %d is die\n",time_milli() - start, m->name);
            return (0);
        }

        pthread_mutex_lock(m->print);
        printf("%ld ms, %d is thinking\n",time_milli() - start, m->name);
        pthread_mutex_unlock(m->print);
    }
    return (0);
}

/*
name philo
1 2 3 4
1 3 ได้กิน   % 2 != 0 lock R
1 แย่ง 2   3 แย่ง 4    % 2 = 0 ไม่ได้กิน
----------
จับเวลาก่อนนอน - เวลาเริ่มกินรอบถัดไป
เวลาเริ่มกินรอบถัดไป - เวลาก่อนนอนของรอบที่ผ่านมา ห้ามเกิน time_die
*/


void    simulation(t_main *m)
{
    int i = 1;

    if (m[0].number == 1)
    {
        printf("%d ms, %d has taken a fork_r\n",0, m->name);
        usleep(m[0].time_die * 1000);
        printf("%d ms, %d is die\n",m[0].time_die, m->name);
        return;
    }
    while (i <= m[0].number)//เลขคี่
    {
        if (m[i - 1].name % 2 != 0)
        {
            pthread_create(&m[i - 1].philo, NULL, &status_philo, (void *)&m[i - 1]);//แตกหน่อ 1
        }
        i++;
    }
    i = 1;
    usleep(100);
    while (i <= m[0].number)//เลขคู่
    {
        if (m[i - 1].name % 2 == 0)
        {
            pthread_create(&m[i - 1].philo, NULL, &status_philo, (void *)&m[i - 1]);//แตกหน่อ
        }
        i++;
    }
    i = 0;
    int jj;
    while (1)
    {
        if (m[i % (m->number)].mod == 1)
        {
            break;
        }
        jj = 0;
        for (int j = 0 ;j < m->number ; ++j)
        {
            if (m[j].mod == 2)
            {
                jj++;
            }
        }
        if (jj == m->number - 1)
            break;
        i++;
    }
}

int main(int argc, char **argv)
{
    t_main  *m; // t_main *p -> ต้อง malloc (สามารถสร้างหลายชิ้นได้)
    int i;

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
    m = initialize_philo(m, argc, argv);//กำหนดค่าให้กับ Philo ทุกคน
    simulation(m);//Philo กินนอนคิด จับเวลา


    pthread_mutex_destroy(&m->print2);
    i = 0;
    while (i < ft_atoi(argv[1]))
    {
        pthread_mutex_destroy(&m[i++].fork_r);
    }
    i = 0;
    while (i < m[0].number)
    {
        pthread_detach(m[i++].philo);
    }
    free(m);
}


//ดูสูตรพี่เน หาเวลาว่าพอมั้ย ไม่พอให้ตาย
