#include "philosophers.h"

void	*start_life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(500);
	philo->last_meal = current_time();
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

void	thread_init(t_philo *philo, int size)
{
	int	i;
	pthread_t monitor;

	i = 0;
	while (i++ < size)
	{
		pthread_create(&(philo->thread), NULL, start_life, philo);
		philo = philo->next;
	}
	if (pthread_create(&monitor, NULL, monitoring, philo))
		return ;
	i = 0;
	pthread_join(monitor, NULL);
	while (i++ < size)
	{
		pthread_join(philo->thread, NULL);
		philo = philo->next;
	}
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
	philos = create_philos(philos, info, size);
	if (!philos)
		return (1);
	thread_init(philos, size);
	clear_up(philos, size);
}
