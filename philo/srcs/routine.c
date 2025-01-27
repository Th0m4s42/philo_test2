/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbasse <thbasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:34:57 by thbasse           #+#    #+#             */
/*   Updated: 2025/01/27 10:02:00 by thbasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static bool	grab_forks(pthread_mutex_t *m1, pthread_mutex_t *m2, t_philo *phil)
{
	if (phil->id % 2 == 0)
	{
		pthread_mutex_lock(m2);
		print_action(phil, "has taken a fork");
		if (check_death(phil) == true)
		{
			pthread_mutex_unlock(m2);
			return (false);
		}
		pthread_mutex_lock(m1);
		print_action(phil, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(m1);
		print_action(phil, "has taken a fork");
		if (check_death(phil) == true)
		{
			pthread_mutex_unlock(m1);
			return (false);
		}
		pthread_mutex_lock(m2);
		print_action(phil, "has taken a fork");
	}
	return (true);
}

static bool	try_to_eat(t_philo *philo)
{
	if (check_death(philo) == true
		|| grab_forks(&philo->fork, &philo->next->fork, philo) == false)
		return (false);
	if (check_death(philo) == true)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		return (false);
	}
	print_action(philo, "is eating");
	philo->last_meal = get_time_ms();
	if (ft_sleep(philo, philo->info->time_to_eat) == false)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		return (false);
	}
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	if (check_exit(philo) == true)
		return (false);
	return (true);
}

static bool	solo_philo(t_philo *philo)
{
	if (philo->info->nb_of_phi == 1)
	{
		pthread_mutex_lock(&philo->fork);
		print_action(philo, "has taken a fork");
		ft_sleep(philo, philo->info->time_to_death);
		try_to_eat(philo);
		pthread_mutex_unlock(&philo->fork);
		return (true);
	}
	return (false);
}

bool	kitkat(t_philo *philo)
{
	size_t	timer;

	timer = 0;
	if (philo->info->time_to_eat > philo->info->time_to_sleep)
		timer = philo->info->time_to_eat - philo->info->time_to_sleep;
	if (philo->info->nb_of_phi % 2 == 1 && philo->id % 2 == 0)
		timer *= 2;
	if (ft_sleep(philo, timer + 5) == false)
		return (false);
	return (true);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (solo_philo(philo) == true)
		return (NULL);
	print_action(philo, "is thinking");
	if (philo->id % 2 == 1)
		usleep(1000);
	while (1)
	{
		if (try_to_eat(philo) == false)
			break ;
		if (check_death(philo) == true || check_all_ate(philo) == true)
			break ;
		print_action(philo, "is sleeping");
		if (ft_sleep(philo, philo->info->time_to_sleep) == false
			|| check_all_ate(philo) == true)
			break ;
		print_action(philo, "is thinking");
		if (check_death(philo) == true || check_all_ate(philo) == true)
			break ;
		if (kitkat(philo) == false || check_all_ate(philo) == true)
			break ;
	}
	return (NULL);
}
