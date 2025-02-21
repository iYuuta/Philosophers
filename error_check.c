#include "Philosophers.h"

void	clear_up(t_philo *philo, int size, int con)
{
	t_philo *tmp;
	t_info *info;
    static int freed;
	int		i;

	i = 0;
	if (!philo)
		return ;
	info = philo->info;
	while (i++ < size)
	{
		tmp = philo;
		philo = philo->next;
		if (con == 1 && i < size - 1)
			pthread_mutex_destroy(&(tmp->fork));
		else if (con == 0)
			pthread_mutex_destroy(&(tmp->fork));
		free(tmp);
		tmp = NULL;
	}
	if (freed == 0 && info)
	{
		freed = 1;
		pthread_mutex_destroy(&(info->death));
		pthread_mutex_destroy(&(info->print));
		free(info);//all the threads try to free this pointer
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