#include "philosophers.h"

int	lone_fella(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork));
	printf("%ld %d has taken a fork\n", (current_time() - philo->info->start_time),
		philo->id);
	ft_usleep(philo->info->time_to_die, philo);
	pthread_mutex_unlock(&(philo->fork));
	return (1);
}

void	eat(t_philo *philo)
{
	if (philo->id == philo->info->philos_number)
		pthread_mutex_lock(&(philo->next->fork));
	else
		pthread_mutex_lock(&(philo->fork));
	if (check_life_status(philo))
	{
		if (philo->id == philo->info->philos_number)
			pthread_mutex_unlock(&(philo->next->fork));
		else
			pthread_mutex_unlock(&(philo->fork));
		return ;
	}
	ft_print("has taken a fork", philo);
	if (philo->id == philo->info->philos_number)
		pthread_mutex_lock(&(philo->fork));
	else
		pthread_mutex_lock(&(philo->next->fork));
	ft_print("has taken a fork", philo);
	ft_print("is eating", philo);
	pthread_mutex_lock(&(philo->eat));
	philo->meals++;
	philo->last_meal = current_time();
	pthread_mutex_unlock(&(philo->eat));
	ft_usleep(philo->info->time_to_eat, philo);
	pthread_mutex_unlock(&(philo->next->fork));
	pthread_mutex_unlock(&(philo->fork));
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
