/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbasse <thbasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 07:57:50 by thbasse           #+#    #+#             */
/*   Updated: 2025/01/27 10:26:50 by thbasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

////////////////////////////////////////////////////////////////////////////////
//								STRUCTURES									  //
////////////////////////////////////////////////////////////////////////////////

typedef struct s_info
{
	int				nb_of_phi;
	size_t			time_to_death;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nb_of_meal;
	size_t			time_start;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	bool			all_ate;
	pthread_mutex_t	all_ate_mutex;
	bool			someone_dead;
}	t_info;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	fork;
	size_t			last_meal;
	int				meal_count;
	pthread_mutex_t	meal_mutex;
	t_info			*info;
	struct s_philo	*next;
}	t_philo;

typedef bool	(*t_array)(char **arg);

////////////////////////////////////////////////////////////////////////////////
//								FONCTIONS									  //
////////////////////////////////////////////////////////////////////////////////

/* *****************************rules**************************************** */

bool	check_rules(int argc, char **argv);
bool	check_is_number(char **arg);
bool	check_len_argument(char **arg);
bool	check_intmax(char **arg);
bool	check_ifphilo(char **arg);

/* *****************************rules_utils********************************** */

long	ft_atol(const char *str);
int		ft_strlen(char *string);
void	ft_putendl_fd(char *str, int fd);
void	init_functionarray(t_array (*funct_array)[5]);

/* *****************************thread*************************************** */

bool	join_threads(pthread_t *ids, int nb_philo, t_philo *first);
bool	init_thread_array(pthread_t **ids, t_info *info, t_philo *first);

/* *****************************routine************************************** */

void	*routine(void *arg);

/* *****************************thread_utils********************************* */

bool	check_exit(t_philo *philo);
bool	check_all_ate(t_philo *philo);
bool	check_death(t_philo *philo);
size_t	get_time_ms(void);
bool	ft_sleep(t_philo *philo, size_t time);

/* *****************************print**************************************** */

void	print_action(t_philo *philo, char *action);

/* *****************************init***************************************** */

bool	intitialization(char **arg, t_info **info, t_philo **philos,
			pthread_t **ids);

/* *****************************main***************************************** */

void	ft_free(t_philo *philo);
void	free_struct(t_info *info, t_philo *first, pthread_t *ids);

#endif