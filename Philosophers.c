#include "Philosophers.h"

long long current_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (((long long)tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void ft_print(char *str, t_philo *philo)
{
    pthread_mutex_lock(&(philo->info->print));
    printf("%llu %d %s\n", (current_time() - philo->info->start_time), philo->id, str);
    pthread_mutex_unlock(&(philo->info->print));
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = current_time();
	while ((current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void    ft_exit(int idk, t_philo *philo, int size)
{
    int i;
    t_philo *tmp;

    tmp = philo;
    i = 0;
    while (i++ < size)
    {
        pthread_join(tmp->thread, NULL);
        tmp = tmp->next;
    }
    clear_up(philo, size, 0);
}

int check_status(t_philo *philo)
{
    if ((current_time() - philo->last_meal) >= philo->info->time_to_die || (philo->info->av5 == 1 && philo->meals == philo->info->number_of_meals))
        return (0);
    return (1);
}
void    *routine(void *philos)
{
    t_philo *philo;

    philo = (t_philo *)philos;
    if (philo->id % 2 == 0)
        ft_usleep(10);
    philo->last_meal = current_time();
    while (philo->info->exit)
    {
        if (!check_status(philo))
        {
            pthread_mutex_lock(&(philo->info->death));
            ft_print("died", philo);
            philo->info->exit = 0;
            ft_exit(0, philo, philo->info->philos_number);
            break;
            pthread_mutex_unlock(&(philo->info->death));
        }
        pthread_mutex_lock(&(philo->fork));
        ft_print("has taken a fork", philo);
        pthread_mutex_lock(&(philo->next->fork));
        ft_print("has taken a fork", philo);
        ft_print("is eating", philo);
        philo->last_meal = current_time();
        ft_usleep(philo->info->time_to_eat);
        philo->meals++;
        if (!check_status(philo))
        {
            pthread_mutex_lock(&(philo->info->death));
            ft_print("died", philo);
            philo->info->exit = 0;
            ft_exit(0, philo, philo->info->philos_number);
            break;
            pthread_mutex_unlock(&(philo->info->death));
        }
        pthread_mutex_unlock(&(philo->fork));
        pthread_mutex_unlock(&(philo->next->fork));
        ft_print("is sleeping", philo);
        ft_usleep(philo->info->time_to_sleep);
        if (!check_status(philo))
        {
            pthread_mutex_lock(&(philo->info->death));
            ft_print("died", philo);
            philo->info->exit = 0;
            ft_exit(0, philo, philo->info->philos_number);
            break;
            pthread_mutex_unlock(&(philo->info->death));
        }
        ft_print("is thinking", philo);
    }
    return NULL;
}

void f()
{
    system("leaks a.out");
}
int main(int ac, char **av)
{
    t_philo *philos;
    t_info *info;
    int size;
    int i = 0;
    
    atexit(f);
    if (check_args(ac, av) == 0)
        return (write(2, "invalid args\n", 13), 1);
    size = atoi(av[1]);
    if (size > 200)
        return (write(2, "too many philosophers\n", 22), 1);
    philos = NULL;
    philos = create_philos(philos, NULL, size);
    if (!philos)
        return (1);
    info = set_info(ac, av);
    if (!info)
        return (clear_up(philos, size, 0), 1);
    while (i < size)
    {
        philos->info = info;
        pthread_create((&philos->thread), NULL, routine, philos);
        philos = philos->next;
        i++;
    }
    i = 0;
    while (i++ < size)
    {
        pthread_join((philos->thread), NULL);
        philos = philos->next;
    }
}
