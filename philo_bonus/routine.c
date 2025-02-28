#include "philosophers.h"

int get_fork(t_philo *philo)
{
	return ((philo->id) % philo->info->philos_number);
}

void	eat(t_philo *philo)
{
	int a;

	sem_wait(philo->info->forks);
	ft_print("has taken a fork", philo, 0);
	a = get_fork(philo);
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