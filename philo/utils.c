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
	if (!philo->info->exit)
	{
		pthread_mutex_unlock(&(philo->info->print));
		return ;
	}
	if (str && str[0] == 'd')
		philo->info->exit = 0;
	printf("%ld %d %s\n", (current_time() - philo->info->start_time),
		philo->id, str);
	pthread_mutex_unlock(&(philo->info->print));
}

int	ft_usleep(long milliseconds, t_philo *philo)
{
	long	start;

	start = current_time();
	while ((current_time() - start) < milliseconds)
	{
		usleep(500);
		if (!philo->info->exit)
			return (0);
	}
	return (0);
}
