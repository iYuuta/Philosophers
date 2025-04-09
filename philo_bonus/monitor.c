#include "philosophers.h"

void	end_life(t_philo *philo)
{
	size_t	i;

	i = 0;
	while (i++ < philo->info->philos_number)
		sem_post(philo->info->terminate);
}

int	check_life_status(t_philo *philo)
{
	if ((current_time() - philo->last_meal) > philo->info->time_to_die)
	{
		ft_print("died", philo, 1);
		philo->died = 0;
		sem_post(philo->info->terminate);
		return (1);
	}
	return (0);
}

int	check_meals(t_philo *philo)
{
	if (philo->info->av5 && philo->meals > philo->info->number_of_meals)
		return (1);
	return (0);
}

int	monitoring(t_philo *philo)
{
	if (!philo->died || check_life_status(philo))
		return (1);
	return (0);
}
