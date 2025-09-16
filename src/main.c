/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luviso-p <luviso-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:25:49 by lalbe             #+#    #+#             */
/*   Updated: 2025/09/16 13:44:01 by luviso-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor_thread;
	int		i;

	if (!validate_arguments(argc, argv))
		return (1);
	data.num_philosophers = safe_atoi(argv[1]);
	data.time_to_die = safe_atoi(argv[2]);
	data.time_to_eat = safe_atoi(argv[3]);
	data.time_to_sleep = safe_atoi(argv[4]);
	if (argc == 6)
		data.number_of_times_each_philosopher_must_eat = safe_atoi(argv[5]);
	else
		data.number_of_times_each_philosopher_must_eat = -1;
	if (!validate_specific_range(&data))
		return (1);
	if (!init_simulation(&data))
	{
		perror("Initialization failed");
		return (1);
	}
	if (pthread_create(&monitor_thread, NULL, monitor_routine, &data) != 0)
	{
		perror("Failed to create monitor thread");
		cleanup(&data);
		return (1);
	}
	i = 0;
	while (i < data.num_philosophers)
	{
		if (pthread_create(&data.threads[i], NULL, philosopher_routine, &data.philosophers[i]) != 0)
		{
			perror("Failed to create thread");
			signal_stop(&data);
			pthread_join(monitor_thread, NULL);
			cleanup_partial_threads(&data, i);
			cleanup(&data);
			return (1);
		}
		i ++;
	}
	pthread_join(monitor_thread, NULL);
	i = 0;
	while (i < data.num_philosophers)
	{
		pthread_join(data.threads[i], NULL);
		i ++;
	}
	cleanup(&data);
	return (0);
}


