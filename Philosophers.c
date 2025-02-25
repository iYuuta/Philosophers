#include "Philosophers.h"

void *start_life(void *arg)
{
    t_philo *philo;
    
    philo = (t_philo *)arg;
    philo->last_meal = current_time();
    while (philo->info->exit)
    {
        eat(philo);
        if (!philo->info->exit)
            break;
        sleeep(philo);
        if (!philo->info->exit)
            break;
        think(philo);
        if (check_meals(philo))
            break ;
        monitoring(philo);
    }
    pthread_mutex_unlock(&(philo->info->print));
    return NULL;
}

int main(int ac, char **av)
{
    t_philo *philos;
    t_info *info;
    int size;
    int i = 0;
    
    if (check_args(ac, av) == 0)
        return (write(2, "invalid args\n", 13), 1);
    size = atoi(av[1]);
    if (size > 200)
        return (write(2, "too many philosophers\n", 22), 1);
    philos = NULL;
    info = set_info(ac, av);
    philos = create_philos(philos, info, size);
    while (i++ < size)
    {
        if (philos->id % 2 == 0)
            usleep(50);
        pthread_create(&(philos->thread), NULL, start_life, philos);
        philos = philos->next;
    }
    i = 0;
    while (i++ < size)
    {
        pthread_join(philos->thread, NULL);
        philos = philos->next;
    }
    clear_up(philos, size);
}
