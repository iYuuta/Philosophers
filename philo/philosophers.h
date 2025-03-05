#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_info
{
	pthread_mutex_t	print;
	pthread_mutex_t	wait;
	int				exit;
	int				av5;
	int				philos_number;
	long			start_time;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_think;
	long			time_to_die;
	long			number_of_meals;

}					t_info;

typedef struct s_philo
{
	int				id;
	long			meals;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	fork;
	struct s_philo	*next;
	struct s_philo	*prev;
	t_info			*info;
}					t_philo;

t_philo	*create_philos(t_philo *philos, t_info *info, int size);
t_info	*set_info(int ac, char **av);
long	current_time(void);
int		check_args(int ac, char **av);
void	clear_up(t_philo *philo, int size);
void	*monitoring(void *philo);

void	think(t_philo *philo);
void	sleeep(t_philo *philo);
void	eat(t_philo *philo);

int		ft_lstsize(t_philo *lst);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo	*ft_lstlast(t_philo *lst);
t_philo	*ft_lstnew(int content);

long	ft_atoi(const char *str);
long	current_time(void);
void	ft_print(char *str, t_philo *philo);
int		ft_usleep(long milliseconds, t_philo *philo);
int		check_meals(t_philo *philo);

#endif