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

static bool	grab_forks(pthread_mutex_t *m1, pthread_mutex_t *m2 , t_philo *philo)
{
	if(check_death(philo) == true)
		return (false);
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(m2);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(m1);
		print_action(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(m1);
		print_action(philo, "has taken a fork");
		pthread_mutex_lock(m2);
		print_action(philo, "has taken a fork");
	}
	// if(m1 < m2)
	// {
	// 	pthread_mutex_lock(m1);
	// 	print_action(philo, "has taken a fork");
	// 	pthread_mutex_lock(m2);
	// 	print_action(philo, "has taken a fork");
	// 	// printf("%zu \n", get_time_ms() - philo->last_meal);
	// }
	// else
	// {
	// 	pthread_mutex_lock(m2);
	// 	print_action(philo, "has taken a fork");
	// 	pthread_mutex_lock(m1);
	// 	print_action(philo, "has taken a fork");
	// 	// printf("%zu \n", get_time_ms() - philo->last_meal);
	// }
	return (true);
}

static bool	try_to_eat(t_philo *philo)
{
	if (grab_forks(&philo->fork, &philo->next->fork, philo) == false)
		return (false);
	if (check_death(philo) == true)
	{
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(&philo->next->fork);
		return (false);
	}
	print_action(philo, "is eating");
	philo->last_meal = get_time_ms();
	philo->meal_count++;
	ft_sleep(philo, philo->info->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	return (true);
}

static bool	solo_philo(t_philo *philo)
{
	if (philo->info->nb_of_phi == 1)
	{
		pthread_mutex_lock(&philo->fork);
		print_action(philo, "has taken a fork");
		if (ft_sleep(philo, philo->info->time_to_death) == false)
		{
			pthread_mutex_unlock(&philo->fork);
			return (true);
		}
		pthread_mutex_unlock(&philo->fork);
		return (true);
	}
	return (false);
}

void	kitkat(t_philo *philo)
{
	size_t	timer;

	if (philo->info->nb_of_phi % 2 == 0)
		return ;
	timer = 0;
	if (philo->info->time_to_eat > philo->info->time_to_sleep)
		timer = philo->info->time_to_eat + 1 - philo->info->time_to_sleep - 2;
	usleep((timer * 1000) + 2000);
}

void	*routine(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	if (solo_philo(philo) == true)
		return (NULL);
	print_action(philo, "is thinking");
	if (philo->id % 2 == 0)
		usleep(500);
	if (philo->info->nb_of_phi == philo->id)
		usleep(philo->info->time_to_eat);
	while (1)
	{
		if (try_to_eat(philo) == false)
			break ;
		if (check_death(philo) == true || check_all_ate(philo) == true)
			break ;
		print_action(philo, "is sleeping");
		ft_sleep(philo, philo->info->time_to_sleep);
		print_action(philo, "is thinking");
		if (check_death(philo) == true)
			break ;
		kitkat(philo);
	}
	return (NULL);
}
