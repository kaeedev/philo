/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalbe <lalbe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:25:49 by lalbe             #+#    #+#             */
/*   Updated: 2025/09/15 13:39:20 by lalbe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

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
}
