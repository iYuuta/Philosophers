/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoayedde <yoayedde@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-28 19:34:24 by yoayedde          #+#    #+#             */
/*   Updated: 2025-02-28 19:34:24 by yoayedde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*ft_lstnew(int content)
{
	t_philo	*strc;

	strc = malloc(sizeof(t_philo));
	if (!strc)
		return (NULL);
	strc->id = content;
	strc->next = strc;
	strc->prev = strc;
	strc->meals = 1;
	return (strc);
}

t_philo	*ft_lstlast(t_philo *lst)
{
	t_philo	*temp;

	if (!lst)
		return (NULL);
	temp = lst;
	if (!temp->next)
		return (lst);
	while (temp->next != lst)
		temp = temp->next;
	return (temp);
}

int	ft_lstsize(t_philo *lst)
{
	int		size;
	t_philo	*temp;

	size = 0;
	if (!lst)
		return (0);
	temp = lst;
	while (temp)
	{
		if (temp->next && temp->next->id < temp->id)
			return (size);
		temp = temp->next;
		size++;
	}
	return (size);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*temp;

	if (!lst || !new)
		return ;
	temp = ft_lstlast(*lst);
	if (temp)
	{
		(*lst)->prev = new;
		new->next = (*lst);
		temp->next = new;
		new->prev = temp;
	}
	else
		*lst = new;
}
