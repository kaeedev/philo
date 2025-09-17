/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luviso-p <luviso-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 14:45:51 by lalbe             #+#    #+#             */
/*   Updated: 2025/09/17 10:26:09 by luviso-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_simulation_over(t_data *data)
{
	int	result;

	pthread_mutex_lock(&data->control_mutex);
	result = data->dead_flag || data->all_ate_enough;
	pthread_mutex_unlock(&data->control_mutex);
	return (result);
}

int	check_philosopher_death(t_data *data)
{
	int	current_time;
	int	last_time_eat;
	int	i;
	int	time_without_eat;

	current_time = get_current_time();
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_lock(&data->control_mutex);
		last_time_eat = data->philosophers[i].last_meal_time;
		pthread_mutex_unlock(&data->control_mutex);
		time_without_eat = current_time - last_time_eat;
		if (time_without_eat >= data->time_to_die)
		{
			print_status(&data->philosophers[i], MSG_DIE);
			pthread_mutex_lock(&data->control_mutex);
			data->dead_flag = TRUE;
			pthread_mutex_unlock(&data->control_mutex);
			return (TRUE);
		}
		i ++;
	}
	return (FALSE);
}

int	check_all_ate_enough(t_data *data)
{
	int	counter_success;
	int	i;
	int	philosopher_eats;

	if (data->number_of_times_each_philosopher_must_eat == -1)
		return (FALSE);
	counter_success = 0;
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_lock(&data->control_mutex);
		philosopher_eats = data->philosophers[i].count_meal_success;
		pthread_mutex_unlock(&data->control_mutex);
		if (philosopher_eats >= data->number_of_times_each_philosopher_must_eat)
			counter_success ++;
		i ++;
	}
	if (counter_success == data->num_philosophers)
	{
		pthread_mutex_lock(&data->control_mutex);
		data->all_ate_enough = TRUE;
		pthread_mutex_unlock(&data->control_mutex);
		return (TRUE);
	}
	return (FALSE);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!is_simulation_over(data))
	{
		if (check_philosopher_death(data))
			break ;
		if (check_all_ate_enough(data))
			break ;
		usleep(100);
	}
	return (NULL);
}