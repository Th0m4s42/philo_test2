/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbasse <thbasse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 08:14:12 by thbasse           #+#    #+#             */
/*   Updated: 2025/01/27 08:14:30 by thbasse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long	ft_atol(const char *str)
{
	long	sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || *str == '\t' || *str == '\v' || *str == '\n'
		|| *str == '\r' || *str == '\f')
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

int	ft_strlen(char *string)
{
	int	i;

	if (string == NULL)
		return (0);
	i = 0;
	while (string[i])
		i++;
	return (i);
}

void	ft_putendl_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

void	init_functionarray(t_array (*funct_array)[5])
{
	(*funct_array)[0] = check_is_number;
	(*funct_array)[1] = check_len_argument;
	(*funct_array)[2] = check_intmax;
	(*funct_array)[3] = check_ifphilo;
	(*funct_array)[4] = NULL;
}
