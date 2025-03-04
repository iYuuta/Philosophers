#include "philosophers.h"

int	lone_fella(t_philo *philo)
{
	ft_usleep(philo->info->time_to_die, philo);
	ft_print("died", philo);
	philo->info->exit = 0;
	pthread_mutex_lock(&(philo->info->print));
	pthread_mutex_unlock(&(philo->fork));
	return (1);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork));
	if (!philo->info->exit)
	{
		pthread_mutex_unlock(&(philo->fork));
		return ;
	}
	ft_print("has taken a fork", philo);
	if (philo->info->philos_number == 1 && lone_fella(philo))
		return ;
	pthread_mutex_lock(&(philo->next->fork));
	if (!philo->info->exit)
	{
		pthread_mutex_unlock(&(philo->next->fork));
		return ;
	}
	ft_print("has taken a fork", philo);
	ft_print("is eating", philo);
	pthread_mutex_lock(&(philo->info->wait));
	philo->meals++;
	philo->last_meal = current_time();
	pthread_mutex_unlock(&(philo->info->wait));
	ft_usleep(philo->info->time_to_eat, philo);
	pthread_mutex_unlock(&(philo->fork));
	pthread_mutex_unlock(&(philo->next->fork));
}

void	sleeep(t_philo *philo)
{
	ft_print("is sleeping", philo);
	ft_usleep(philo->info->time_to_sleep, philo);
}

void	think(t_philo *philo)
{
	ft_print("is thinking", philo);
	ft_usleep(philo->info->time_to_think, philo);
}
