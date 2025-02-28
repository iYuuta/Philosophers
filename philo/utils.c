#include "philosophers.h"

size_t	ft_atoi(const char *str)
{
	int			i;
	size_t	    result;

	i = 0;
	result = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result);
}

long long current_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (((long long)tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_print(char *str, t_philo *philo)
{
    pthread_mutex_lock(&(philo->info->print));
    if (!philo->info->exit)
    {
        pthread_mutex_unlock(&(philo->info->print));
        return ;
    }
    printf("%llu %d %s\n", (current_time() - philo->info->start_time), philo->id, str);
    pthread_mutex_unlock(&(philo->info->print));
}

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = current_time();
	while ((current_time() - start) < milliseconds)
    {
        usleep(500);
        pthread_mutex_lock(&(philo->info->wait1));
        if (check_life_status(philo))
        {
            philo->info->exit = 0;
            pthread_mutex_unlock(&(philo->info->wait1));
            return 0;
        }
        pthread_mutex_unlock(&(philo->info->wait1));
    }
	return (0);
}
