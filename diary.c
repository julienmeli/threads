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

int	simonoff(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->sim->sim_mutex[OFF]);
	if (philo->sim->sim_on_off == 0)
	{
		return (pthread_mutex_unlock(&philo->sim->sim_mutex[OFF]));
	}
	else
		return (pthread_mutex_unlock(&philo->sim->sim_mutex[OFF]) + 1);
}

void	release_all_forks(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->nb_philos)
	{
		release_forks(&sim->philosopher[i]);
		i++;
	}
}

int	sudden_death(t_philosopher *philo)
{
	struct timeval  current_time;
        long int        check_time;

	gettimeofday(&current_time, NULL);
        check_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
        check_time = check_time - philo->sim->start_time;
	printf("id %d check_time: %ld time of last meal: %ld time to die: %d\n", philo->id, check_time, philo->time_of_last_meal, philo->sim->time_to_die);
	if ((check_time - philo->time_of_last_meal) > philo->sim->time_to_die)
	{
		release_forks(philo);
		printf("here? id: %d\n", philo->id);
		ft_log(check_time, philo, "died.");
		pthread_mutex_lock(&philo->sim->sim_mutex[OFF]);
		philo->sim->sim_on_off = 0;
		release_all_forks(philo->sim);
		puts("bloque?");
		pthread_mutex_unlock(&philo->sim->sim_mutex[OFF]);
		return (1);
	}
	else
		return (0);
}

void	ft_log(long int time, t_philosopher *philo, char *str)
{
	pthread_mutex_lock(&philo->sim->sim_mutex[LOG]);
	//if (philo->sim->sim_on_off == 1)
	if (simonoff(philo))
		printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->sim->sim_mutex[LOG]);
}
