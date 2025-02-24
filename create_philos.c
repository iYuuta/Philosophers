#include "Philosophers.h"

t_info *set_info(int ac, char **av)
{
    t_info *info;

    info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);//protect
    info->philos_number = atoi(av[1]);
	pthread_mutex_init(&(info->print), NULL);
	info->exit = 1;
	info->dead = 1;
    info->start_time = current_time();
    info->time_to_die = atoi(av[2]);
    info->time_to_eat = atoi(av[3]);
    info->time_to_sleep = atoi(av[4]);
	info->av5 = 0;
    if (ac > 5)
	{
        info->number_of_meals = atoi(av[5]);
		info->av5 = 1;
	}
    return (info);
}

t_philo *create_philos(t_philo *philos, t_info *info, int size)
{
    t_philo *tmp;
    int i;

    i = -1;
    while (++i < size)
    {
        tmp = ft_lstnew(i + 1);
        if (!tmp)
            return (clear_up(philos, i), NULL);
        tmp->info = info;
        if (pthread_mutex_init(&(tmp->fork), NULL) != 0)
            return (clear_up(philos, i), NULL);
        ft_lstadd_back(&philos, tmp);
    }
    return (philos);
}
