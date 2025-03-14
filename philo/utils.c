#include "philosophers.h"

long	ft_atoi(const char *str)
{
	int			i;
	long		result;

	i = 0;
	result = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result);
}

long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((long)tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_print(char *str, t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->print));
	// printf("%d locked print ft_print\n", philo->id);
	if (check_life_status(philo))
	{
		pthread_mutex_unlock(&(philo->info->print));
		return ;
	}
	if (str && str[0] == 'd')
	{
		pthread_mutex_lock(&(philo->info->wait));
		philo->info->exit = 0;
		pthread_mutex_unlock(&(philo->info->wait));
	}
	printf("%ld %d %s\n", (current_time() - philo->info->start_time),
		philo->id, str);
	if (check_life_status(philo))
	{
		pthread_mutex_unlock(&(philo->info->print));
		return ;
	}
	// printf("%d unlocked print ft_print\n", philo->id);
	pthread_mutex_unlock(&(philo->info->print));
}

int	ft_usleep(long milliseconds, t_philo *philo)
{
	long	start;

	start = current_time();
	while ((current_time() - start) < milliseconds)
	{
		usleep(500);
		if (check_life_status(philo))
		{
			return (0);
		}
	}
	return (0);
}
