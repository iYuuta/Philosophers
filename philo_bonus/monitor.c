#include "philosophers.h"

int check_life_status(t_philo *philo)
{
    if ((current_time() - philo->last_meal) > philo->info->time_to_die)
    {
        ft_print("died", philo, 0);
        philo->died = 0;
        return (1);    
    }
    return (0);
}

int check_meals(t_philo *philo)
{
    if (philo->info->av5 && philo->meals > philo->info->number_of_meals)
    {
        return (1);
    }
    return (0);
}

int monitoring(t_philo *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    if (!philo->died || check_life_status(philo))
    {
        sem_close(philo->info->wait);
        return (1);
    }
    return (0);
}
