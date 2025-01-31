/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diary.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 07:52:38 by jmeli             #+#    #+#             */
/*   Updated: 2025/01/30 13:09:49 by jmeli            ###   ########.fr       */
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

int	sudden_death(t_philosopher *philo)
{
	struct timeval	current_time;
	long int		check_time;

	gettimeofday(&current_time, NULL);
	check_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	check_time = check_time - philo->sim->start_time;
	if ((check_time - philo->time_of_last_meal) > philo->sim->time_to_die)
	{
		release_forks(philo);
		ft_log(check_time, philo, "died.");
		pthread_mutex_lock(&philo->sim->sim_mutex[OFF]);
		philo->sim->sim_on_off = 0;
		release_all_forks(philo->sim);
		pthread_mutex_unlock(&philo->sim->sim_mutex[OFF]);
		return (1);
	}
	else
		return (0);
}

void	ft_log(long int time, t_philosopher *philo, char *str)
{
	pthread_mutex_lock(&philo->sim->sim_mutex[LOG]);
	if (simonoff(philo))
		printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->sim->sim_mutex[LOG]);
}
