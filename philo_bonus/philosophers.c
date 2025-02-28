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
	i = -1;
	if (philo->info->av5)
	{
		while (++i < size)
			waitpid(pid[i], NULL, 0);
		clear_up(philo, size);
		return (free(pid), 0);
	}
	sem_wait(philo->info->terminate);
	while (++i < size)
		kill(pid[i], SIGTERM);
	return (clear_up(philo, size), free(pid), 0);
}

int main(int ac, char **av)
{
	int *pid;
	t_philo *philo = NULL;
	t_info *info;
	int	size;

	if (check_args(ac, av) == 0)
        return (write(2, "invalid args\n", 13), 1);
    size = ft_atoi(av[1]);
	pid = malloc(sizeof(int) * (size + 1));
	if (!pid)
		return (write(2, "malloc failed\n", 14), 1);
	info = set_info(ac, av);
	philo = create_philos(philo, info, size);
	sem_wait(philo->info->terminate);
    if (size > 200)
	{
		return (write(2, "too many philosophers\n", 22), 1);
	}
	process_init(philo, pid, size);
	return (0);
}
