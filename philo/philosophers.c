#include "philosophers.h"

void	join_threads(t_philo *philo, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->prev;
		i++;
	}
}

void	*start_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_meal = current_time();
	if (philo->id % 2 == 0)
		ft_usleep(10, philo);
	while (philo->info->exit)
	{
		eat(philo);
		if (!philo->info->exit)
			break ;
		sleeep(philo);
		if (!philo->info->exit)
			break ;
		think(philo);
		if (check_meals(philo))
			return (NULL);
	}
	pthread_mutex_unlock(&(philo->info->print));
	return (NULL);
}

int	thread_init(t_philo *philo, int size)
{
	int			i;
	pthread_t	monitor;

	i = -1;
	while (++i < size)
	{
		if (pthread_create(&(philo->thread), NULL, start_life, philo))
			return (join_threads(philo, i), 1);
		philo = philo->next;
	}
	if (pthread_create(&monitor, NULL, monitoring, philo))
		return (join_threads(philo, i), 1);
	i = 0;
	pthread_join(monitor, NULL);
	while (i++ < size)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_info	*info;
	int		size;

	if (check_args(ac, av) == 0)
		return (write(2, "invalid args\n", 13), 1);
	size = ft_atoi(av[1]);
	if (size > 200)
		return (write(2, "too many philosophers\n", 22), 1);
	philos = NULL;
	info = set_info(ac, av);
	if (!info)
		return (1);
	if (info->av5 && info->number_of_meals == 0)
		return (free(info), 0);
	philos = create_philos(philos, info, size);
	if (!philos)
		return (1);
	if (thread_init(philos, size))
		return (1);
	return (clear_up(philos, size), 0);
}
