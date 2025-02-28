#include "philosophers.h"

void	destroy_sem(t_info *info)
{
	sem_unlink("/wait");
	sem_unlink("/terminate");
	sem_unlink("/forks");
	sem_close(info->forks);
	sem_close(info->wait);
	sem_close(info->terminate);
}

void	clear_up(t_philo *philo, int size)
{
	t_philo	*tmp;
	t_info	*info;
	int		i;

	i = 0;
	if (!philo)
		return ;
	info = philo->info;
	while (i++ < size)
	{
		tmp = philo;
		philo = philo->next;
		free(tmp);
		tmp = NULL;
	}
	destroy_sem(info);
	free(info);
}

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (0);
	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
		}
	}
	return (1);
}
