/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbasse <thbasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 23:54:00 by thbasse           #+#    #+#             */
/*   Updated: 2025/01/28 00:08:29 by thbasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	free_linked_list(t_philo *first)
{
	t_philo	*tmp;

	tmp = first;
	while (first != NULL)
	{
		free(first);
		first = tmp;
		tmp = tmp->next;
	}
}
