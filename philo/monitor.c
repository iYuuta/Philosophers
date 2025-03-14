#include "philosophers.h"

int	check_meals(t_philo *philo)
{
	pthread_mutex_lock(&(philo->eat));
    if (philo->info->av5 && philo->meals >= philo->info->number_of_meals)
	{
		return (pthread_mutex_unlock(&(philo->eat)), 1);
	}
	pthread_mutex_unlock(&(philo->eat));
    return (0);
}

int check_life_status(t_philo *philo)
{
    pthread_mutex_lock(&(philo->info->wait));
    if (!philo->info->exit)
	    return (pthread_mutex_unlock(&(philo->info->wait)), 1);
    pthread_mutex_unlock(&(philo->info->wait));
    return (0);
}
int check_last_meals(t_philo *philo)
{
	pthread_mutex_lock(&(philo->eat));
	if (current_time() > philo->info->time_to_die + philo->last_meal)
        return (pthread_mutex_unlock(&(philo->eat)), 1);
	pthread_mutex_unlock(&(philo->eat));
	return (0);
}

void	*monitoring(void *arg)
{
    t_philo	*philo;
    int		meals;

    meals = 0;
    philo = (t_philo *)arg;
    usleep(1000);
    while (1)
    {
        pthread_mutex_lock(&(philo->eat));
        if (philo->info->av5 && philo->meals >= philo->info->number_of_meals)
        {
            meals++;
            philo->meals++;
            pthread_mutex_unlock(&(philo->eat));
            if (meals == philo->info->philos_number)
                return (NULL);
        }
        else
        {
            pthread_mutex_unlock(&(philo->eat));
            if (check_last_meals(philo))
            {
                ft_print("died", philo);
                return (NULL);
            }
        }
        philo = philo->next;
    }
    return (NULL);
}
