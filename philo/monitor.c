#include "philosophers.h"

int	check_meals(t_philo *philo)
{
	if (philo->info->av5 && philo->meals > philo->info->number_of_meals)
		return (1);
	return (0);
}

void	*monitoring(void *arg)
{
	t_philo *philo;
	int		meals;

	meals = 1;
	philo = (t_philo *)arg;
	usleep(500);
	while (1)
	{
		if (philo->info->av5 && !philo->done_eating && check_meals(philo))
		{
			philo->done_eating = 1;
			meals++;
		}
		else if (current_time() > philo->info->time_to_die + philo->last_meal)
		{
			pthread_mutex_lock(&(philo->info->wait));
			ft_print("died", philo);
			pthread_mutex_unlock(&(philo->info->wait));
			return (NULL);
		}
		if (meals == philo->info->philos_number)
			return (NULL);
		philo = philo->next;
	}
	return (NULL);
}
