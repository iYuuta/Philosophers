#include "philosophers.h"

void	clear_up(t_philo *philo, int size)
{
	t_philo		*tmp;
	t_info		*info;
	static int	freed;
	int			i;

	i = 0;
	if (!philo)
		return ;
	info = philo->info;
	while (i++ < size)
	{
		tmp = philo;
		philo = philo->next;
		pthread_mutex_destroy(&(tmp->fork));
		free(tmp);
		tmp = NULL;
	}
	if (freed == 0 && info)
	{
		freed = 1;
		pthread_mutex_destroy(&(info->print));
		pthread_mutex_destroy(&(info->wait));
		free(info);
	}
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
