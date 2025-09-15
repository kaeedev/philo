/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalbe <lalbe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:45:51 by lalbe             #+#    #+#             */
/*   Updated: 2025/09/15 14:52:10 by lalbe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_simulation_over(t_philosopher *philo)
{
	int	result;

	pthread_mutex_lock(&philo->data->control_mutex);
	result = philo->data->dead_flag || philo->data->all_ate_enough;
	pthread_mutex_unlock(&philo->data->control_mutex);
	return (result);
}
