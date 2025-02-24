#include "Philosophers.h"

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
        if (!philo->info->exit)
            return 0;
    }
	return (0);
}