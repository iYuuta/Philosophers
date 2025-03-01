/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoayedde <yoayedde@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-28 19:34:27 by yoayedde          #+#    #+#             */
/*   Updated: 2025-02-28 19:34:27 by yoayedde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_life_status(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->wait2));
	if ((current_time() - philo->last_meal) > philo->info->time_to_die)
	{
		ft_print("died", philo);
		philo->info->exit = 0;
		pthread_mutex_unlock(&(philo->info->wait2));
		return (1);
	}
	pthread_mutex_unlock(&(philo->info->wait2));
	return (0);
}

int	check_meals(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->wait2));
	if (philo->info->av5 && philo->meals > philo->info->number_of_meals)
	{
		pthread_mutex_unlock(&(philo->info->wait2));
		return (1);
	}
	pthread_mutex_unlock(&(philo->info->wait2));
	return (0);
}

int	monitoring(t_philo *philo)
{
	pthread_mutex_lock(&(philo->info->wait1));
	if (!philo->info->exit || check_life_status(philo))
	{
		pthread_mutex_lock(&(philo->info->print));
		pthread_mutex_unlock(&(philo->info->wait1));
		return (1);
	}
	pthread_mutex_unlock(&(philo->info->wait1));
	return (0);
}
