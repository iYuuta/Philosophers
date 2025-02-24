#include "Philosophers.h"

void    eat(t_philo *philo)
{
    pthread_mutex_lock(&(philo->fork));
    ft_print("has taken a fork", philo);
    if (philo->info->philos_number == 1)
    {
        ft_usleep(philo->info->time_to_die, philo);
        ft_print(" died", philo);
        philo->info->exit = 0;
        pthread_mutex_lock(&(philo->info->print));
        return ;
    }
    pthread_mutex_lock(&(philo->next->fork));
    ft_print("has taken a fork", philo);
    ft_print(" is eating", philo);
    ft_usleep(philo->info->time_to_eat, philo);
    pthread_mutex_unlock(&(philo->next->fork));
    pthread_mutex_unlock(&(philo->fork));
    philo->meals++;
    philo->last_meal = current_time();
    monitoring(philo);
}

void sleeep(t_philo *philo)
{
    ft_print(" is sleeping", philo);
    ft_usleep(philo->info->time_to_sleep, philo);
}

void think(t_philo *philo)
{
    ft_print(" is thinking", philo);
}