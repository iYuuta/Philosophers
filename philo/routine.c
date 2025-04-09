#include "philosophers.h"

int	lone_fella(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork));
	printf("%ld %d has taken a fork\n",
		(current_time() - philo->info->start_time),
		philo->id);
	ft_usleep(philo->info->time_to_die, philo);
	pthread_mutex_unlock(&(philo->fork));
	return (1);
}

void	eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*sec_fork;

	first_fork = &(philo->fork);
	sec_fork = &(philo->next->fork);
	if (philo->id == philo->info->philos_number)
	{
		first_fork = &(philo->next->fork);
		sec_fork = &(philo->fork);
	}
	pthread_mutex_lock(first_fork);
	ft_print("has taken a fork", philo);
	pthread_mutex_lock(sec_fork);
	ft_print("has taken a fork", philo);
	ft_print("is eating", philo);
	pthread_mutex_lock(&(philo->eat));
	philo->meals++;
	philo->last_meal = current_time();
	pthread_mutex_unlock(&(philo->eat));
	ft_usleep(philo->info->time_to_eat, philo);
	pthread_mutex_unlock(sec_fork);
	pthread_mutex_unlock(first_fork);
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
