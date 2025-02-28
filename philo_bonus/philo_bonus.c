#include "philosophers.h"

int	start_life(t_philo *philo)
{
	int i = 0;
	pthread_t monitoring;
	while (1)
	{
		eat(philo);
		if (current_time() - philo->last_meal > philo->info->time_to_die)
		{
			ft_print("died", philo, 1);
			sem_post(philo->info->terminate);
		}
		sleeep(philo);
		if (current_time() - philo->last_meal > philo->info->time_to_die)
		{
			ft_print("died", philo, 1);
			sem_post(philo->info->terminate);
		}
		think(philo);
		if (current_time() - philo->last_meal > philo->info->time_to_die)
		{
			ft_print("died", philo, 1);
			sem_post(philo->info->terminate);
		}
	}
}

int main(int ac, char **av)
{
	int *pid;
	t_philo *philo;
	t_info *info;
	int	con;
	int	size;
	int i;

	if (check_args(ac, av) == 0)
        return (write(2, "invalid args\n", 13), 1);
    size = atoi(av[1]);
	pid = malloc(sizeof(int) * (size + 1));
	if (!pid)
		return (write(2, "malloc failed\n", 14), 1);
	pid[size] = 0;
	i = 0;
	info = set_info(ac, av);
	philo = create_philos(philo, info, size);
	sem_wait(philo->info->terminate);
    if (size > 200)
        return (write(2, "too many philosophers\n", 22), 1);
	while (i < size)
	{
		pid[i] = fork();
		if (pid[i] < 0)
			return (free(pid), write(2, "fork failed\n", 12), 1);
		if (pid[i] == 0)
		{
			con = start_life(philo);
			break ;
		}
		philo = philo->next;
		i++;
	}
	i = -1;
	sem_wait(philo->info->terminate);
	while (++i < size)
		kill(pid[i], SIGTERM);
	return (0);
}