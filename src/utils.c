/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luviso-p <luviso-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:57:56 by luviso-p          #+#    #+#             */
/*   Updated: 2025/09/12 14:21:00 by luviso-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int is_valid_number (char *str)
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

int safe_atoi(char *str)
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

int validate_specific_range();