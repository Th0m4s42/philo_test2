/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbasse <thbasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:20:54 by thbasse           #+#    #+#             */
/*   Updated: 2025/01/27 08:22:33 by thbasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	print_action(t_philo *philo, char *action)
{
	size_t	time;

	pthread_mutex_lock(&philo->info->death_mutex);
	if (philo->info->someone_dead == true)
	{
		pthread_mutex_unlock(&philo->info->death_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->info->death_mutex);
	pthread_mutex_lock(&philo->info->print_mutex);
	time = get_time_ms() - philo->info->time_start;
	printf("%zu %d %s\n", time, philo->id, action);
	pthread_mutex_unlock(&philo->info->print_mutex);
}
