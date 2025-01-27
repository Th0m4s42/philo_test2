/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbasse <thbasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:19:51 by thbasse           #+#    #+#             */
/*   Updated: 2025/01/27 08:31:01 by thbasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	join_threads(pthread_t *ids, int nb_philo, t_philo *first)
{
	int	i;

	i = 0;
	first->info->time_start = get_time_ms();
	while (i < nb_philo)
	{
		first->last_meal = first->info->time_start;
		if (pthread_join(ids[i], NULL) != 0)
		{
			ft_putendl_fd("Thread join failed", 2);
			return (false);
		}
		first = first->next;
		i++;
	}
	return (true);
}

bool	init_thread_array(pthread_t **ids, t_info *info, t_philo *first)
{
	int	i;

	*ids = malloc(sizeof(pthread_t) * info->nb_of_phi);
	if (*ids == NULL)
	{
		ft_putendl_fd("Malloc failed in: init_thread_array", 2);
		return (false);
	}
	i = 0;
	while (i < info->nb_of_phi)
	{
		if (pthread_create(&*((*ids) + i), NULL, routine, (void *) first) != 0)
		{
			ft_putendl_fd("Failed to create thread", 2);
			return (false);
		}
		i++;
		first = first->next;
	}
	return (true);
}
