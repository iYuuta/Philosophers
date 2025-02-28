#include "philosophers.h"

void	eat(t_philo *philo)
{
	sem_wait(philo->info->forks);
	ft_print("has taken a fork", philo, 0);
	if (philo->info->philos_number == 1)
	{
		ft_usleep(philo->info->time_to_die, philo);
		ft_print("died", philo, 0);
		philo->died = 0;
		sem_post(philo->info->terminate);
		sem_wait(philo->info->wait);
		return ;
	}
	sem_wait(philo->info->forks);
	ft_print("has taken a fork", philo, 0);
	philo->last_meal = current_time();
	philo->meals++;
	ft_print("is eating", philo, 0);
	ft_usleep(philo->info->time_to_eat, philo);
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
}

void	sleeep(t_philo *philo)
{
	ft_print("is sleeping", philo, 0);
	ft_usleep(philo->info->time_to_sleep, philo);
}

void	think(t_philo *philo)
{
	ft_print("is thinking", philo, 0);
	ft_usleep(philo->info->time_to_think, philo);
}