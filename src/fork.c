/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luviso-p <luviso-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:07:02 by luviso-p          #+#    #+#             */
/*   Updated: 2025/09/16 13:51:36 by luviso-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	take_forks(t_philosopher *philo)
{
	if (philo->data->num_philosophers == 1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->id_fork_left]);
		print_status(philo, MSG_FORK);
		return (0);
	}
	if (philo->id_fork_left < philo->id_fork_right)
	{
		pthread_mutex_lock(&philo->data->forks[philo->id_fork_left]);
		print_status(philo, MSG_FORK);
		pthread_mutex_lock(&philo->data->forks[philo->id_fork_right]);
		print_status(philo, MSG_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[philo->id_fork_right]);
		print_status(philo, MSG_FORK);
		pthread_mutex_lock(&philo->data->forks[philo->id_fork_left]);
		print_status(philo, MSG_FORK);
	}
	return (1);
}

void	drop_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->id_fork_left]);
	pthread_mutex_unlock(&philo->data->forks[philo->id_fork_right]);
}
