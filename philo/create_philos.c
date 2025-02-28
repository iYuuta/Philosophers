#include "philosophers.h"

t_info	*init_mutex(t_info *info)
{
	if (pthread_mutex_init(&(info->print), NULL))
	{
		return (free(info), NULL);
	}
	if (pthread_mutex_init(&(info->wait1), NULL))
	{
		return (pthread_mutex_destroy(&(info->print)), free(info), NULL);
	}
	if (pthread_mutex_init(&(info->wait2), NULL))
	{
		return (pthread_mutex_destroy(&(info->print)),
			pthread_mutex_destroy(&(info->wait1)), free(info), NULL);
	}
	return (info);
}

t_info	*set_info(int ac, char **av)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info = init_mutex(info);
	if (!info)
		return (NULL);
	info->philos_number = atoi(av[1]);
	info->exit = 1;
	info->start_time = current_time();
	info->time_to_die = atoi(av[2]);
	info->time_to_eat = atoi(av[3]);
	info->time_to_sleep = atoi(av[4]);
	info->time_to_think = 0;
	if (info->time_to_eat > info->time_to_sleep)
		info->time_to_think = info->time_to_eat - info->time_to_sleep;
	info->av5 = 0;
	if (ac > 5)
	{
		info->number_of_meals = atoi(av[5]);
		info->av5 = 1;
	}
	return (info);
}

t_philo	*create_philos(t_philo *philos, t_info *info, int size)
{
	t_philo	*tmp;
	int		i;

	i = -1;
	while (++i < size)
	{
		tmp = ft_lstnew(i + 1);
		if (!tmp)
			return (clear_up(philos, i), free(info), info = NULL, NULL);
		tmp->info = info;
		if (pthread_mutex_init(&(tmp->fork), NULL) != 0)
			return (clear_up(philos, i), NULL);
		ft_lstadd_back(&philos, tmp);
	}
	return (philos);
}
