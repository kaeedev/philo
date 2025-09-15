/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalbe <lalbe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 13:41:58 by luviso-p          #+#    #+#             */
/*   Updated: 2025/09/15 11:34:37 by lalbe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_arguments(int argc, char **argv)
{
	int	i;

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
		if (!get_value(argv[i]))
			return (0);
		i ++;
	}
	return (1);
}
