/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luviso-p <luviso-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 13:21:08 by lalbe             #+#    #+#             */
/*   Updated: 2025/09/16 13:50:51 by luviso-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philosopher *philo, char *action)
{
	long long	current_time;
	long long	timestamp;

	pthread_mutex_lock(&philo->data->print_mutex);
	current_time = get_current_time();
	timestamp = current_time - philo->data->start_time;
	printf("%lld %d %s\n", timestamp, philo->id_philosopher, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	think_action(t_philosopher *philo)
{
	print_status(philo, MSG_THINK);
	precise_sleep(1);
}

void	sleep_action(t_philosopher *philo)
{
	print_status(philo, MSG_SLEEP);
	precise_sleep(philo->data->time_to_sleep);
}

void	eat_action(t_philosopher *philo)
{

	if (!take_forks(philo))
		return ;
	if (is_simulation_over(philo->data))
	{
		drop_forks(philo);
		return ;
	}
	print_status(philo, MSG_EAT);
	pthread_mutex_lock(&philo->data->control_mutex);
	philo->last_meal_time = get_current_time();
	philo->count_meal_success = philo->count_meal_success + 1;
	pthread_mutex_unlock(&philo->data->control_mutex);
	precise_sleep(philo->data->time_to_eat);
	drop_forks(philo);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	think_action(philo);
	while (1)
	{
		eat_action(philo);
		if (is_simulation_over(philo->data))
			break ;
		sleep_action(philo);
		if (is_simulation_over(philo->data))
			break ;
		think_action(philo);
	}
	return (NULL);
}
