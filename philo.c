#include "philo.h"

long time_milli(void)
{
	struct timeval time_now;

	gettimeofday(&time_now, NULL);
	return (((time_now.tv_sec * 1000) + (time_now.tv_usec / 1000)));
}

void	initial_value(t_main *m, int i, int argc, char **argv)
{
	if (i == ft_atoi(argv[1]))//สำหรับคนสุดท้าย ให้มือซ้ายหยิบส้อม
		m[i - 1].l_fork = &m[0].fork_r;
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
	m[i - 1].full = 0;
	m[i - 1].after_eat_time = 0;
	m[i - 1].mod = 0;
	m[i - 1].argc = argc;
	m[i - 1].start = 0;
	if (argc == 6)
		m[i - 1].must_eat = ft_atoi(argv[5]);
	else if (argc == 5)
		m[i - 1].must_eat = 0;
}


t_main *initialize_philo(t_main *m, int argc, char **argv) //แปลว่าเริ่มต้น ให้ค่า(การเตรียมข้อมูล)
{
	int     i;

	i = 1;
	m = malloc(sizeof(t_main) * ft_atoi(argv[1]));//จองตามจำนวน Philo
	pthread_mutex_init(&m[0].fork_r,NULL); // philo คนที่ 1 (ตัวถัดๆไป บรรทัดที่ 37)


	while (i <= ft_atoi(argv[1]))//วนให้ค่าตามจำนวน Philo
	{
		initial_value(m, i, argc, argv);
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

/*
return 1 ตาย
return 0 ไม่ตาย*/

int    is_philo_dead(t_main *m, int activity)
{
	long    remain_life;

	remain_life = ((m->time_die) - (time_milli() - m->after_eat_time));

	if ((remain_life - activity) <= 0)
	{
		if (remain_life < 0)
			remain_life = remain_life * -1;
		usleep((remain_life) * 1000);
		m->mod = 1;
		pthread_mutex_lock(m->print);
		printf("%ld ms, %d is die\n",time_milli() - m->start, m->name);
		return (1);
	}
	usleep(activity * 1000);
	return(0);
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

/*
return 1 ตาย
return 0 ไม่ตาย*/

int	is_one_philo(t_main *m)
{
	if (m->number == 1)
	{
		printf("%d ms, %d has taken a fork_r\n",0, m->name);
		usleep(m->time_die * 1000);
		printf("%d ms, %d is die\n",m->time_die, m->name);
		m->mod = 1;
		return (1);
	}
	return (0);
}

void    *status_philo(void *input)
{
	t_main *m;

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
// int	sleep_to_eat(t_main *m)
// {
// 		// ft_print(m, 4);
// 		// if (is_philo_dead(m, m->time_sleep) == 1)
// 		// 	return;
// 		// ft_print(m, 5);
// }

void	ft_print(t_main *m, int mode_print)
{
		pthread_mutex_lock(m->print);
		if (mode_print == 1)
			printf("%ld ms, %d has taken a fork_r\n",time_milli() - m->start, m->name);
		else if (mode_print == 2)
			printf("%ld ms, %d has taken a l_fork\n",time_milli() - m->start, m->name);
		else if (mode_print == 3)
			printf("%ld ms, %d is eating\n",time_milli() - m->start, m->name);
		else if (mode_print == 4)
			printf("%ld ms, %d is sleeping\n", time_milli() - m->start, m->name);
		else if (mode_print == 5)
			printf("%ld ms, %d is thinking\n",time_milli() - m->start, m->name);
		pthread_mutex_unlock(m->print);
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

void	check_end(t_main *m)
{
	int	i;
	int	j;
	int	philo_full;

	i = 0;
	while (1)
	{
		if (m[i % (m->number)].mod == 1)
			break;
		if (m->argc == 6)
		{
			j = 0;
			philo_full = 0;
			while (j < m->number)
			{
				if (m[j].full == 1)
					philo_full++;
				j++;
			}
			if (philo_full == m->number)
				break;
			i++;
		}
	}
}


void    simulation(t_main *m)
{
	int i;

	i = 1;
	while (i <= m[0].number)//เลขคี่
	{
		if (m[i - 1].name % 2 != 0)
			pthread_create(&m[i - 1].philo, NULL, &status_philo, (void *)&m[i - 1]);//แตกหน่อ 1
		i++;
	}
	i = 1;
	usleep(100);
	while (i <= m[0].number)//เลขคู่
	{
		if (m[i - 1].name % 2 == 0)
			pthread_create(&m[i - 1].philo, NULL, &status_philo, (void *)&m[i - 1]);//แตกหน่อ
		i++;
	}

	check_end(m);
}

void	ft_free_all(t_main *m)
{
	int	i;

	pthread_mutex_destroy(&m->print2);
	i = 0;
	while (i < m[0].number)
		pthread_mutex_destroy(&m[i++].fork_r);
	i = 0;
	while (i < m[0].number)
		pthread_detach(m[i++].philo);
	free(m);
}

int	main(int argc, char **argv)
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
	ft_free_all(m);
}
