/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbasse <thbasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 07:58:39 by thbasse           #+#    #+#             */
/*   Updated: 2025/01/27 07:59:27 by thbasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	check_rules(int argc, char **arg)
{
	t_array	checking[5];
	int		i;

	if (argc < 5 || argc > 6)
	{
		ft_putendl_fd("Wrong format: try ./philo nb nb nb nb (nb)", 2);
		return (false);
	}
	i = 0;
	init_functionarray(&checking);
	while (checking[i])
	{
		if (checking[i](arg) == false)
			return (false);
		i++;
	}
	return (true);
}

bool	check_is_number(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				ft_putendl_fd("philo use ONLY numbers", 2);
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	check_len_argument(char **arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (ft_strlen(arg[i]) > 10)
		{
			ft_putendl_fd("int_max is the limit", 2);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_intmax(char **arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (ft_atol(arg[i]) > INT_MAX)
		{
			ft_putendl_fd("int_max is the limit", 2);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_ifphilo(char **arg)
{
	if (ft_atol(arg[1]) == 0)
	{
		ft_putendl_fd("Needs atleast 1 philosopher", 2);
		return (false);
	}
	return (true);
}
