/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbasse <thbasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:51:53 by thbasse           #+#    #+#             */
/*   Updated: 2025/01/27 10:30:21 by thbasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	check_exit(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->info->all_ate_mutex);
	if (philo->info->nb_of_meal == -1)
	{
		pthread_mutex_unlock(&philo->info->all_ate_mutex);
		return (false);
	}
	pthread_mutex_unlock(&philo->info->all_ate_mutex);
	if (check_death(philo) == true)
		return (true);
	i = 0;
	while (i++ <= philo->info->nb_of_phi)
	{
		pthread_mutex_lock(&philo->meal_mutex);
		if (philo->meal_count < philo->info->nb_of_meal)
			return (pthread_mutex_unlock(&philo->meal_mutex), false);
		pthread_mutex_unlock(&philo->meal_mutex);
		philo = philo->next;
	}
	pthread_mutex_lock(&philo->info->all_ate_mutex);
	philo->info->all_ate = true;
	pthread_mutex_unlock(&philo->info->all_ate_mutex);
	return (true);
}

bool	check_all_ate(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->all_ate_mutex);
	if (philo->info->all_ate == true)
	{
		pthread_mutex_unlock(&philo->info->all_ate_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->all_ate_mutex);
	return (false);
}

bool	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->death_mutex);
	if (philo->info->someone_dead == true)
	{
		pthread_mutex_unlock(&philo->info->death_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->death_mutex);
	if (get_time_ms() - philo->last_meal >= philo->info->time_to_death)
	{
		pthread_mutex_lock(&philo->info->death_mutex);
		if (philo->info->someone_dead == true)
		{
			pthread_mutex_unlock(&philo->info->death_mutex);
			return (true);
		}
		philo->info->someone_dead = true;
		pthread_mutex_lock(&philo->info->print_mutex);
		printf("%zu %d died\n", get_time_ms() - philo->info->time_start,
			philo->id);
		pthread_mutex_unlock(&philo->info->print_mutex);
		pthread_mutex_unlock(&philo->info->death_mutex);
		return (true);
	}
	return (false);
}

size_t	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

bool	ft_sleep(t_philo *philo, size_t time)
{
	size_t	start;

	start = get_time_ms();
	while (get_time_ms() - start < time)
	{
		if (check_death(philo) == true)
			return (false);
		usleep(1000);
	}
	return (true);
}
