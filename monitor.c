#include "Philosophers.h"

int check_life_status(t_philo *philo)
{
    if ((current_time() - philo->last_meal) >= philo->info->time_to_die)
    {
        ft_print(" died", philo);
        philo->info->exit = 0;
        return (1);    
    }    
    return (0);
}

int check_meals(t_philo *philo)
{
    if (philo->info->av5 && philo->meals >= philo->info->number_of_meals)
    {
        philo->info->exit = 0;
        return (1);   
    }
    return (0);
}

int monitoring(t_philo *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    if (!philo->info->exit || check_life_status(philo) || check_meals(philo))
    {
        pthread_mutex_lock(&(philo->info->print));
        return (1);
    }
    return (0);
}
