#include "philosophers.h"

t_info *init_forks(t_info *info, int size)
{
    int i;

    i = -1;
    sem_unlink("/wait");
    sem_unlink("/terminate");
    info->wait = sem_open("/wait", O_CREAT | O_TRUNC, 0666, 1);
    if (!info->wait)
        return (NULL);
    info->terminate = sem_open("/terminate", O_CREAT | O_TRUNC, 0666, 1);
    if (!info->terminate)
        return (NULL);
    sem_unlink("/forks");
    info->forks = sem_open("/forks", O_CREAT | O_TRUNC, 0666, size);
    if (!info->forks)
        return (sem_close(info->wait), NULL);
    return (info);
}

t_info *set_info(int ac, char **av)
{
    t_info *info;

    info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
    info->philos_number = atoi(av[1]);
    info->forks = malloc(sizeof(sem_t *) * info->philos_number);
    if (!info->forks)
        return (free(info), NULL);
    info = init_forks(info, info->philos_number);
    if (!info)
        return (free(info->forks), free(info), NULL);
    info->start_time = current_time();
    info->time_to_die = atoi(av[2]);
    info->time_to_eat = atoi(av[3]);
    info->time_to_sleep = atoi(av[4]);
    info->time_to_think = 0;
    if (info->time_to_eat > info->time_to_sleep)
    {
        info->time_to_think = info->time_to_eat - info->time_to_sleep;
    }
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
    int     i;

    i = -1;
    while (++i < size)
    {
        tmp = ft_lstnew(i + 1);
        if (!tmp)
            return (clear_up(philos, i), free(info), info = NULL, NULL);
        tmp->info = info;
        ft_lstadd_back(&philos, tmp);
    }
    return (philos);
}
