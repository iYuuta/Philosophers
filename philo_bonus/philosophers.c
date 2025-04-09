#include "philosophers.h"

int	start_life(t_philo *philo)
{
	philo->last_meal = current_time();
	if (philo->id % 2 == 0)
		usleep(200);
	while (1)
	{
		eat(philo);
		if (!philo->died)
		{
			sem_post(philo->info->terminate);
		}
		if (check_meals(philo))
			exit(0);
		sleeep(philo);
		if (!philo->died)
		{
			sem_post(philo->info->terminate);
		}
		think(philo);
		if (!philo->died)
		{
			sem_post(philo->info->terminate);
		}
	}
}

void	*term_childp(void *arg)
{
	size_t	i;
	t_philo	*philo;

	i = -1;
	philo = (t_philo *)arg;
	sem_wait(philo->info->terminate);
	while (++i < philo->info->philos_number)
		kill(philo->info->pid[i], SIGTERM);
	return (NULL);
}

int	finish_life(t_philo *philo, int *pid, int size)
{
	int			i;
	pthread_t	term;

	i = -1;
	pthread_create(&term, NULL, term_childp, philo);
	while (++i < size)
		waitpid(pid[i], NULL, 0);
	sem_post(philo->info->terminate);
	pthread_join(term, NULL);
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
		philo->info->pid = pid;
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
		return (write(2, "Error\n", 6), 1);
	pid = malloc(sizeof(int) * (size + 1));
	if (!pid)
		return (write(2, "malloc failed\n", 14), 1);
	info = set_info(ac, av);
	if (!info)
		return (1);
	if (info->av5 && info->number_of_meals == 0)
		return (free(info), free(pid), 0);
	philo = create_philos(philo, info, size);
	if (!philo)
		return (free(info), 1);
	sem_wait(philo->info->terminate);
	process_init(philo, pid, size);
	return (clear_up(philo, size), 0);
}
