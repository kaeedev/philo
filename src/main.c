/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luviso-p <luviso-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:25:49 by lalbe             #+#    #+#             */
/*   Updated: 2025/09/17 12:43:43 by luviso-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_arguments(int argc, char **argv, t_data *data)
{
	if (!validate_arguments(argc, argv))
		return (0);
	data->num_philosophers = safe_atoi(argv[1]);
	data->time_to_die = safe_atoi(argv[2]);
	data->time_to_eat = safe_atoi(argv[3]);
	data->time_to_sleep = safe_atoi(argv[4]);
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = safe_atoi(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	if (!validate_specific_range(data))
		return (0);
	return (1);
}

int	create_monitor_thread(t_data *data, pthread_t *monitor_thread)
{
	if (pthread_create(monitor_thread, NULL, monitor_routine, data) != 0)
	{
		perror("Failed to create monitor thread");
		cleanup(data);
		return (0);
	}
	return (1);
}

int	create_philosopher_threads(t_data *data, pthread_t *monitor_thread)
{
	int	i;

	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_create(&data->threads[i], NULL, philosopher_routine, &data->philosophers[i]) != 0)
		{
			perror("Failed to create thread");
			signal_stop(data);
			pthread_join(*monitor_thread, NULL);
			cleanup_partial_threads(data, i);
			cleanup(data);
			return (0);
		}
		i ++;
	}
	return (1);
}

void	join_all_threads(t_data *data, pthread_t *monitor_thread)
{
	int	i;

	pthread_join(*monitor_thread, NULL);
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_join(data->threads[i], NULL);
		i ++;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor_thread;

	if (!parse_arguments(argc, argv, &data))
		return (1);
	if (!init_simulation(&data))
	{
		perror("Initialization failed");
		return (1);
	}
	if (!create_monitor_thread(&data, &monitor_thread))
		return (1);
	if (!create_philosopher_threads(&data, &monitor_thread))
		return (1);
	join_all_threads(&data, &monitor_thread);
	cleanup(&data);
	return (0);
}



