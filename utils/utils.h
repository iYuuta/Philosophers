#ifndef UTILS_H
#define UTILS_H
#include "../Philosophers.h"

struct s_philo;
typedef struct s_philo t_philo;

int	ft_lstsize(t_philo *lst);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
t_philo	*ft_lstlast(t_philo *lst);
t_philo	*ft_lstnew(int content);

#endif