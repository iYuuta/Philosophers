#include "philosophers.h"

int lone_fella(t_philo *philo)
{
    if (philo->info->philos_number == 1)
    {
        ft_usleep(philo->info->time_to_die, philo);
        ft_print("died", philo);
        philo->info->exit = 0;
        pthread_mutex_lock(&(philo->info->print));
        pthread_mutex_unlock(&(philo->fork));
        return (1);
    }
    return (0);
}
void    eat(t_philo *philo)
{
    if (philo->id < philo->next->id)
        pthread_mutex_lock(&(philo->fork));
    else
        pthread_mutex_lock(&(philo->next->fork));
    if (!philo->info->exit)
    {
        pthread_mutex_unlock(&(philo->fork));
        return ;
    }
    ft_print("has taken a fork", philo);
    if (lone_fella(philo))
        return ;
    if (philo->id < philo->next->id)
        pthread_mutex_lock(&(philo->next->fork));
    else
        pthread_mutex_lock(&(philo->fork));
    ft_print("has taken a fork", philo);
    ft_print("is eating", philo);
    philo->meals++;
    philo->last_meal = current_time();
    ft_usleep(philo->info->time_to_eat, philo);
    pthread_mutex_unlock(&(philo->next->fork));
    pthread_mutex_unlock(&(philo->fork));
    monitoring(philo);
}

void sleeep(t_philo *philo)
{
    ft_print("is sleeping", philo);
    ft_usleep(philo->info->time_to_sleep, philo);
}

void think(t_philo *philo)
{
    ft_print("is thinking", philo);
    ft_usleep(philo->info->time_to_think, philo);
}
