/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoayedde <yoayedde@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-28 19:35:05 by yoayedde          #+#    #+#             */
/*   Updated: 2025-02-28 19:35:05 by yoayedde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>

typedef struct s_info
{
	sem_t	*forks;
	sem_t	*wait;
	sem_t	*terminate;
	int		av5;
	size_t	start_time;
	size_t	philos_number;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	time_to_think;
	size_t	time_to_die;
	size_t	number_of_meals;
}			t_info;

typedef struct s_philo
{
	int				id;
	int				died;
	size_t			meals;
	size_t			last_meal;
	struct s_philo	*next;
	struct s_philo	*prev;
	t_info			*info;
}					t_philo;

t_philo	*create_philos(t_philo *philos, t_info *info, int size);
t_info	*set_info(int ac, char **av);
int		check_args(int ac, char **av);
void	clear_up(t_philo *philo, int size);

t_philo	*ft_lstnew(int content);
t_philo	*ft_lstlast(t_philo *lst);
void	ft_lstadd_back(t_philo **lst, t_philo *new);

size_t	ft_atoi(const char *str);
size_t	current_time(void);
int		ft_usleep(size_t milliseconds, t_philo *philo);
void	ft_print(char *str, t_philo *philo, int con);

void	eat(t_philo *philo);
void	sleeep(t_philo *philo);
void	think(t_philo *philo);
int		monitoring(t_philo *arg);
int		check_meals(t_philo *philo);

#endif
