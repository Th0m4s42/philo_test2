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
	int i;

	while (philo->info->all_ate == false)
	{
		if (check_death(philo) == true)
			return (true);
		i = 0;
		pthread_mutex_lock(&philo->meal_mutex);
		while (i < philo->info->nb_of_phi
			&& philo[i].meal_count >= philo->info->nb_of_meal)
			i++;
		pthread_mutex_unlock(&philo->meal_mutex);
		if (i == philo->info->nb_of_phi)
		{
			pthread_mutex_lock(&philo->info->all_ate_mutex);
			philo->info->all_ate = true;
			pthread_mutex_unlock(&philo->info->all_ate_mutex);
			return (true);
		}
	}
	return (false);
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
	if (get_time_ms() - philo->last_meal >= philo->info->time_to_death)
	{
		print_action(philo, "died");
		pthread_mutex_lock(&philo->info->death_mutex);
		philo->info->someone_dead = true;
		pthread_mutex_unlock(&philo->info->death_mutex);
		return (true);
	}
	pthread_mutex_lock(&philo->info->death_mutex);
	if (philo->info->someone_dead == true)
	{
		pthread_mutex_unlock(&philo->info->death_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->death_mutex);
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
