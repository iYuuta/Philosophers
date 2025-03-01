/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoayedde <yoayedde@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-28 19:35:20 by yoayedde          #+#    #+#             */
/*   Updated: 2025-02-28 19:35:20 by yoayedde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_atoi(const char *str)
{
	int			i;
	size_t		result;

	i = 0;
	result = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result);
}

size_t	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((size_t)tv.tv_sec * 1000) + (size_t)(tv.tv_usec / 1000));
}

void	ft_print(char *str, t_philo *philo, int con)
{
	sem_wait(philo->info->wait);
	printf("%zu %d %s\n", (current_time() - philo->info->start_time),
		philo->id, str);
	if (!con)
		sem_post(philo->info->wait);
}

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = current_time();
	while ((current_time() - start) < milliseconds)
	{
		if (monitoring(philo))
			return (0);
		usleep(500);
	}
	return (0);
}
