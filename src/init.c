/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luviso-p <luviso-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 12:14:30 by lalbe             #+#    #+#             */
/*   Updated: 2025/09/16 12:57:10 by luviso-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate_memory(t_data *data)
{
	data->philosophers = malloc(sizeof(t_philosopher) * data->num_philosophers);
	if (!data->philosophers)
	{
		perror("Error allocating memory for philosophers");
		return (0);
	}
	data->threads = malloc(sizeof(pthread_t) * data->num_philosophers);
	if (!data->threads)
	{
		perror("Error allocating memory for threads");
		free(data->philosophers);
		return (0);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (!data->forks)
	{
		perror("Error allocating memory for forks");
		free(data->philosophers);
		free(data->threads);
		return (0);
	}
	return (1);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
	{
		perror("Error: Failed to initialize print mutex");
		return (0);
	}
	if (pthread_mutex_init(&data->control_mutex, NULL) != 0)
	{
		perror("Error: Failed to initialize control mutex");
		return (0);
	}
	while (i < data->num_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			perror("Error: Failed to initialize fork mutex");
			return (0);
		}
		i ++;
	}
	return (1);
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		data->philosophers[i].id_philosopher = i + 1;
		data->philosophers[i].count_meal_success = 0;
		data->philosophers[i].last_meal_time = data->start_time;
		data->philosophers[i].data = data;
		data->philosophers[i].id_fork_left = i;
		data->philosophers[i].id_fork_right = (i + 1) % data->num_philosophers;
		i ++;
	}
	return (1);
}

int	init_simulation(t_data *data)
{
	data->start_time = get_current_time();
	data->dead_flag = 0;
	data->all_ate_enough = 0;
	data->finished_eating = 0;
	if (!allocate_memory(data))
		return (0);
	if (!init_mutex(data))
		return (0);
	if (!init_philosophers(data))
		return (0);
	return (1);
}
