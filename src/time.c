/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luviso-p <luviso-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:46:07 by lalbe             #+#    #+#             */
/*   Updated: 2025/09/17 10:24:41 by luviso-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	time_diff(long long start, long long end)
{
	return (end - start);
}

void	precise_sleep(t_philosopher *philo, long duration_ms)
{
	long long	start_time;

	start_time = get_current_time();
	while ((get_current_time() - start_time) < duration_ms)
	{
		if (is_simulation_over(philo->data))
			return ;
		usleep(100);
	}
}
