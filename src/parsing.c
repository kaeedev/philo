/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luviso-p <luviso-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:41:58 by luviso-p          #+#    #+#             */
/*   Updated: 2025/09/12 14:20:16 by luviso-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_arguments(int argc, char **argv)
{
	int	i;
	int	value;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("ERROR. WRONG NUMBER OF ARGUMENTS");
		return (0);
	}
	while (i < argc)
	{
		if (!is_valid_number(argv[i]))
		{
			printf("ERROR. Argument %d is not a valid number \n", i);
			return (0);
		}
		value = safe_atoi(argv[i]);
		if (value == -1)
		{
			printf("Error. Argument %d is too large\n", i);
			return (0);
		}
		if (value < 0)
		{
			printf("Error. Argument %d is negative\n", i);
			return (0);
		}
		i ++;
	}
		return (1);
}