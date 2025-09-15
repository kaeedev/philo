/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalbe <lalbe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:57:56 by luviso-p          #+#    #+#             */
/*   Updated: 2025/09/15 12:28:29 by lalbe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i ++;
	}
	return (1);
}

int	safe_atoi(char *str)
{
	long	result;

	result = 0;
	while (*str)
	{
		result = result * 10 + *str - '0';
		if (result > INT_MAX)
			return (-1);
		str ++;
	}
	return ((int)result);
}

int	validate_specific_range(t_data *data)
{
	if (data == NULL)
	{
		printf("Error: Invalid data structure");
		return (0);
	}
	if (data->num_philosophers == 0 || data->time_to_die == 0
		|| data->time_to_eat == 0 || data->time_to_sleep == 0)
	{
		printf("Error: Numbers of arguments must be greater than 0");
		return (0);
	}
	if (data->number_of_times_each_philosopher_must_eat != -1
		&& data->number_of_times_each_philosopher_must_eat == 0)
	{
		printf("Error: number_of_times must be greater than 0");
		return (0);
	}
	if (data->num_philosophers == 1)
		printf("With 1 philosopher, they will die (cannot eat with 1 fork)");
	return (1);
}

int	get_value(char *argv)
{
	int	value;

	value = safe_atoi(argv);
	if (value == -1)
	{
		printf("Error. Argument is too large\n");
		return (0);
	}
	if (value < 0)
	{
		printf("Error. Argument is negative\n");
		return (0);
	}
	return (1);
}
