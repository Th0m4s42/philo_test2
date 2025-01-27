/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbasse <thbasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:03:49 by thbasse           #+#    #+#             */
/*   Updated: 2025/01/27 09:20:11 by thbasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	philo_add_back(t_philo **first, t_philo *philo)
{
	t_philo	*tmp;

	if (*first == NULL)
	{
		*first = philo;
		return ;
	}
	tmp = *first;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = philo;
}

static t_philo	*init_philo(t_info *info)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
	{
		ft_putendl_fd("Malloc failed in: init_philo", 2);
		return (NULL);
	}
	philo->id = 0;
	philo->last_meal = info->time_start;
	philo->meal_count = 0;
	pthread_mutex_init(&philo->meal_mutex, NULL);
	pthread_mutex_init(&philo->fork, NULL);
	philo->next = NULL;
	philo->info = info;
	return (philo);
}

static t_philo	*init_philo_list(t_info *info)
{
	t_philo	*first;
	t_philo	*tmp;
	int		i;

	first = NULL;
	i = 0;
	while (i < info->nb_of_phi)
	{
		tmp = init_philo(info);
		if (tmp == NULL)
		{
			ft_free(first);
			return (NULL);
		}
		tmp->id = i + 1;
		philo_add_back(&first, tmp);
		i++;
	}
	tmp->next = first;
	return (first);
}

static t_info	*init_info(char **arg)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (info == NULL)
	{
		ft_putendl_fd("Malloc failed in: init_info", 2);
		return (NULL);
	}
	info->time_start = get_time_ms();
	pthread_mutex_init(&info->print_mutex, NULL);
	pthread_mutex_init(&info->death_mutex, NULL);
	info->all_ate = false;
	pthread_mutex_init(&info->all_ate_mutex, NULL);
	info->nb_of_phi = (int)ft_atol(arg[1]);
	info->time_to_death = (size_t)ft_atol(arg[2]);
	info->time_to_eat = (size_t)ft_atol(arg[3]);
	info->time_to_sleep = (size_t)ft_atol(arg[4]);
	if (arg[5] == NULL)
		info->nb_of_meal = -1;
	else
		info->nb_of_meal = (int)ft_atol(arg[5]);
	info->someone_dead = false;
	return (info);
}

bool	intitialization(char **arg, t_info **info, t_philo **philos,
							pthread_t **ids)
{
	*info = init_info(arg);
	if (info == NULL)
		return (false);
	*philos = init_philo_list(*info);
	if (philos == NULL)
	{
		free_struct(*info, NULL, NULL);
		return (false);
	}
	if (init_thread_array(ids, *info, *philos) == false)
	{
		free_struct(*info, *philos, NULL);
		return (false);
	}
	return (true);
}
