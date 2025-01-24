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

int	sudden_death(t_philosopher *philo)
{
	struct timeval  current_time;
        long int        check_time;

	gettimeofday(&current_time, NULL);
        check_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
        check_time = check_time - philo->sim->start_time;
	if ((check_time - philo->time_of_last_meal) > philo->sim->time_to_die)
	{
		philo->sim->sim_on_off = 0;
		ft_log(check_time, philo, "died.");
		return (1);
	}
	else
		return (0);
}

void	ft_log(long int time, t_philosopher *philo, char *str)
{
	pthread_mutex_lock(&philo->sim->sim_mutex[0]);
	printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->sim->sim_mutex[0]);
}
