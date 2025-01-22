/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diary.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 07:52:38 by jmeli             #+#    #+#             */
/*   Updated: 2025/01/22 14:20:01 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	ft_putnbr(unsigned long int nb)
{
	if (nb > 10)
		ft_putnbr(nb / 10);
	ft_putchar(nb % 10 + '0');
}

void	ft_log(long int time, t_philosopher *philo, char *str)
{
	pthread_mutex_lock(&philo->sim->sim_mutex[0]);
	printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->sim->sim_mutex[0]);
}
