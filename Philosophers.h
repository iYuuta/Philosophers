#ifndef PHILOSOPHERS
#define PHILOSOPHERS

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_info
{
    pthread_mutex_t print;
    int             exit;
    int             av5;
    int     philos_number;
    long long  start_time;
    long long  time_to_eat;
    long long  time_to_sleep;
    long long  time_to_die;
    int     number_of_meals;

}   t_info;

typedef struct s_philo
{
    int             id;
    int             meals;
    long long       last_meal;
    pthread_t       thread;
    pthread_mutex_t fork;
    struct s_philo  *next;
    struct s_philo  *prev;
    t_info          *info;
}       t_philo;

t_philo     *create_philos(t_philo *philos, t_info *info, int size);
t_info      *set_info(int ac, char **av);
long long   current_time(void);
int         check_args(int ac, char **av);
void	    clear_up(t_philo *philo, int size);
int         monitoring(t_philo *arg);

void    think(t_philo *philo);
void    sleeep(t_philo *philo);
void    eat(t_philo *philo);

int	ft_lstsize(t_philo *lst);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo	*ft_lstlast(t_philo *lst);
t_philo	*ft_lstnew(int content);

long long current_time(void);
void ft_print(char *str, t_philo *philo);
int	ft_usleep(size_t milliseconds, t_philo *philo);
int check_meals(t_philo *philo);

#endif