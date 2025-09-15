/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalbe <lalbe@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:44:52 by luviso-p          #+#    #+#             */
/*   Updated: 2025/09/15 14:53:03 by lalbe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define TRUE 1
# define FALSE 0

# define THINKING 0
# define EATING 1
# define SLEEPING 2
# define DEAD 3

# define MSG_FORK "has taken a fork"
# define MSG_EAT "is eating"
# define MSG_SLEEP "is sleeping"
# define MSG_THINK "is thinking"
# define MSG_DIE "died"

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_philosopher
{
	int				id_philosopher; //identificador para cada filosofo
	int				count_meal_success; //numero de comidas completadas
	int				id_fork_left; //indice del tenedor izquierdo
	int				id_fork_right; //indice del tenedor derecho
	long long		last_meal_time; //timestamp de la ultima comida
	struct s_data	*data; //puntero a datos globales
}	t_philosopher;

typedef struct s_data
{
	int				num_philosophers; //numero total de filosofos
	int				time_to_die; //tiempo maximo sin comer antes de morir(ms)
	int				time_to_sleep; //duracion del estado de dormir (ms)
	int				time_to_eat; //duracion del estado de comer (ms)
	int				number_of_times_each_philosopher_must_eat; //comidas requeridas (opcional)
	int				finished_eating; //contador de filosofos que completaron comidas
	int				all_ate_enough; //flag: TRUE si todos comieron suficiente
	int				dead_flag; //flag: TRUE si algun filosofo murio
	long long		start_time; //timestamp inicio de simulacion
	pthread_t		*threads; //array de hilos de filosofos
	pthread_mutex_t	print_mutex; //protege la salida de logs
	pthread_mutex_t	*forks; //array de mutex (uno por tenedor)
	pthread_mutex_t	control_mutex; //protege variables de control
	t_philosopher	*philosophers; //array de estructuras de filosofos
}	t_data;

int			is_valid_number(char *str);
int			safe_atoi(char *str);
int			validate_specific_range(t_data *data);
int			get_value(char *argv);
int			validate_arguments(int argc, char **argv);
long long	get_current_time(void);
long long	time_diff(long long start, long long end);
void		precise_sleep(long long duration_ms);
int			init_mutex(t_data *data);
int			init_philosophers(t_data *data);
int			init_simulation(t_data *data);
int			allocate_memory(t_data *data);
void		print_status(t_philosopher *philo, char *action);
void		think_action(t_philosopher *philo);
void		sleep_action(t_philosopher *philo);
void		eat_action(t_philosopher *philo);
int			is_simulation_over(t_philosopher *philo);
void		*philosopher_routine(void *arg)
#endif