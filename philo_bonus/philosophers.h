#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>
#include <limits.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <semaphore.h>

typedef struct s_info
{
	sem_t			*forks;
	sem_t			*wait;
	sem_t			*terminate;
    int             av5;
    long long       start_time;
    long long       philos_number;
    long long       time_to_eat;
    long long       time_to_sleep;
    long long       time_to_think;
    long long       time_to_die;
    long long       number_of_meals;
}   t_info;

typedef struct s_philo
{
    int             id;
    int             died;
    long long       meals;
    long long       last_meal;
    struct s_philo  *next;
    struct s_philo  *prev;
    t_info          *info;
}       t_philo;

t_philo *create_philos(t_philo *philos, t_info *info, int size);
t_info *set_info(int ac, char **av);
int	check_args(int ac, char **av);
void	clear_up(t_philo *philo, int size);

t_philo	*ft_lstnew(int content);
t_philo	*ft_lstlast(t_philo *lst);
void ft_lstadd_back(t_philo **lst, t_philo *new);

size_t	ft_atoi(const char *str);
long long current_time(void);
int	ft_usleep(size_t milliseconds, t_philo *philo);
void ft_print(char *str, t_philo *philo, int con);

void	eat(t_philo *philo);
void	sleeep(t_philo *philo);
void	think(t_philo *philo);
int     monitoring(t_philo *arg);
int     check_meals(t_philo *philo);

#endif