/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:30:42 by jmeli             #+#    #+#             */
/*   Updated: 2025/01/22 12:18:15 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	ft_is_digit(char c)
{
	if ( c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	ft_str_is_all_pos_int(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_is_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_arguments(int argc, char **argv)
{
	int	i;

	if (argc >= 5 && argc <= 6)
	{
		i = 1;
		while (i < argc)
		{
			if (!argv[i])
				return (0);
			if (!ft_str_is_all_pos_int(argv[i]))
				return (0);
			i++;
		}
	}
	else
		return (0);
	//puts("chekeiros");
	if (ft_atoi(argv[1]) == 0)
	{
		return (0);
	}
	else if (argv[5] && ft_atoi(argv[5]) == 0)
	{
		return (0);
	}
	else
	{
		return (1);
	}
}
