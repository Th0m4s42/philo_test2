/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbasse <thbasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:00:13 by thbasse           #+#    #+#             */
/*   Updated: 2025/01/27 10:28:33 by thbasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	ft_free(t_philo *philo)
{
	t_philo	*tmp;
	int		i;
	int		nb;

	tmp = philo;
	i = 0;
	nb = philo->info->nb_of_phi;
	while (i < nb)
	{
		tmp = philo->next;
		free(philo);
		philo = tmp;
		i++;
	}
}

void	free_struct(t_info *info, t_philo *first, pthread_t *ids)
{
	if (first != NULL)
	{
		pthread_mutex_destroy(&first->fork);
		pthread_mutex_destroy(&first->meal_mutex);
		ft_free(first);
	}
	if (info != NULL)
	{
		pthread_mutex_destroy(&info->print_mutex);
		pthread_mutex_destroy(&info->death_mutex);
		pthread_mutex_destroy(&info->all_ate_mutex);
		free(info);
	}
	if (ids != NULL)
		free(ids);
}

int	main(int argc, char **argv)
{
	t_info		*info;
	t_philo		*philos;
	pthread_t	*ids;

	if (check_rules(argc, argv) == false)
		return (1);
	if (intitialization(argv, &info, &philos, &ids) == false)
	{
		free_struct(info, philos, ids);
		return (1);
	}
	if (join_threads(ids, info->nb_of_phi) == false)
	{
		free_struct(info, philos, ids);
		return (1);
	}
	free_struct(info, philos, ids);
	return (0);
}
