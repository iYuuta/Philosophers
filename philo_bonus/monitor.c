/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoayedde <yoayedde@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-28 19:34:57 by yoayedde          #+#    #+#             */
/*   Updated: 2025-02-28 19:34:57 by yoayedde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_life_status(t_philo *philo)
{
	if ((current_time() - philo->last_meal) > philo->info->time_to_die)
	{
		ft_print("died", philo, 1);
		philo->died = 0;
		return (1);
	}
	return (0);
}

int	check_meals(t_philo *philo)
{
	if (philo->info->av5 && philo->meals > philo->info->number_of_meals)
		return (1);
	return (0);
}

int	monitoring(t_philo *philo)
{
	if (!philo->died || check_life_status(philo))
		return (1);
	return (0);
}
