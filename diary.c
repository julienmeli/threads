/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diary.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 07:52:38 by jmeli             #+#    #+#             */
/*   Updated: 2025/02/05 11:34:08 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	ft_log(long int time, t_philosopher *philo, char *str)
{
	pthread_mutex_lock(&philo->sim->sim_mutex[LOG]);
	usleep(150);
	if (simonoff(philo))
		printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->sim->sim_mutex[LOG]);
}
