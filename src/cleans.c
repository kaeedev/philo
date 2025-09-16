/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleans.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luviso-p <luviso-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 13:21:44 by luviso-p          #+#    #+#             */
/*   Updated: 2025/09/16 13:36:24 by luviso-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	cleanup(t_data *data)
{
	int	i;

	if (data == NULL)
		return ;
	i = 0;
	while (i < data->num_philosophers)
	{
		if (pthread_mutex_destroy(&data->forks[i]) != 0)
			perror("Error destroying fork mutex");
		i ++;
	}
	if (pthread_mutex_destroy(&data->print_mutex) != 0)
		perror("Error destroying print mutex");
	if (pthread_mutex_destroy(&data->control_mutex) != 0)
		perror("Error destroying control mutex");
	free(data->forks);
	free(data->threads);
	free(data->philosophers);
}

void	signal_stop(t_data *data)
{
	if (data == NULL)
		return ;
	pthread_mutex_lock(&data->control_mutex);
	data->dead_flag = TRUE;
	pthread_mutex_unlock(&data->control_mutex);
}

void	cleanup_partial_threads(t_data *data, int created_count)
{
	int	i;

	if (data == NULL || created_count <= 0)
		return ;
	signal_stop(data);
	i = 0;
	while (i < created_count)
	{
		pthread_join(data->threads[i], NULL);
		i ++;
	}
}