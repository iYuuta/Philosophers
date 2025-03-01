/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoayedde <yoayedde@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-28 19:34:46 by yoayedde          #+#    #+#             */
/*   Updated: 2025-02-28 19:34:46 by yoayedde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_death(t_info *info)
{
	if ((info->time_to_die < info->time_to_eat * 2)
		|| info->time_to_die < info->time_to_eat + info->time_to_sleep)
		return (0);
	return (1);
}

t_info	*init_forks(t_info *info, int size)
{
	sem_unlink("/wait");
	sem_unlink("/terminate");
	info->wait = sem_open("/wait", O_CREAT, 0666, 1);
	if (!info->wait)
		return (NULL);
	info->terminate = sem_open("/terminate", O_CREAT, 0666, 1);
	if (!info->terminate)
		return (NULL);
	sem_unlink("/forks");
	info->forks = sem_open("/forks", O_CREAT, 0666, size);
	if (!info->forks)
		return (sem_close(info->wait), NULL);
	return (info);
}

t_info	*set_info(int ac, char **av)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->philos_number = ft_atoi(av[1]);
	info = init_forks(info, info->philos_number);
	if (!info)
		return (free(info), NULL);
	info->start_time = current_time();
	info->time_to_die = ft_atoi(av[2]);
	info->time_to_eat = ft_atoi(av[3]);
	info->time_to_sleep = ft_atoi(av[4]);
	info->time_to_think = 0;
	if (info->time_to_eat > info->time_to_sleep)
	{
		info->time_to_think = info->time_to_eat - info->time_to_sleep;
	}
	info->av5 = 0;
	if (ac > 5)
	{
		info->number_of_meals = ft_atoi(av[5]);
		info->av5 = ft_death(info);
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
		ft_lstadd_back(&philos, tmp);
	}
	return (philos);
}
