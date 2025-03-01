/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoayedde <yoayedde@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-28 19:35:02 by yoayedde          #+#    #+#             */
/*   Updated: 2025-02-28 19:35:02 by yoayedde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	start_life(t_philo *philo)
{
	philo->last_meal = current_time();
	while (1)
	{
		eat(philo);
		if (!philo->died)
		{
			sem_post(philo->info->terminate);
		}
		sleeep(philo);
		if (!philo->died)
		{
			sem_post(philo->info->terminate);
		}
		think(philo);
		if (check_meals(philo))
			exit(0);
		if (!philo->died)
		{
			sem_post(philo->info->terminate);
		}
	}
}

int	finish_life(t_philo *philo, int *pid, int size)
{
	int	i;

	i = -1;
	if (philo->info->av5)
	{
		while (++i < size)
			waitpid(pid[i], NULL, 0);
		return (free(pid), 0);
	}
	sem_wait(philo->info->terminate);
	while (++i < size)
		kill(pid[i], SIGTERM);
	return (free(pid), 0);
}

int	process_init(t_philo *philo, int *pid, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			while (--i >= 0)
				kill(pid[i], SIGTERM);
			return (free(pid), write(2, "fork failed\n", 12), 1);
		}
		if (pid[i] == 0)
		{
			start_life(philo);
			break ;
		}
		philo = philo->next;
	}
	return (finish_life(philo, pid, size));
}

int	main(int ac, char **av)
{
	int		*pid;
	t_philo	*philo;
	t_info	*info;
	size_t	size;

	philo = NULL;
	if (check_args(ac, av) == 0)
		return (write(2, "invalid args\n", 13), 1);
	size = ft_atoi(av[1]);
	if (size > 200 || size == 0)
	{
		return (write(2, "Error\n", 6), 1);
	}
	pid = malloc(sizeof(int) * (size + 1));
	if (!pid)
		return (write(2, "malloc failed\n", 14), 1);
	info = set_info(ac, av);
	philo = create_philos(philo, info, size);
	sem_wait(philo->info->terminate);
	process_init(philo, pid, size);
	clear_up(philo, size);
	return (0);
}
