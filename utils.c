/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:02:36 by jmeli             #+#    #+#             */
/*   Updated: 2025/02/04 10:55:30 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	left_right_fork(t_philosopher *philo, int l_fork, int r_fork)
{
	if (philo->id == 1)
	{
		pthread_mutex_lock(&philo->sim->philo_mutex[l_fork]);
		philo->left_hand = 1;
	}
	else
	{
		pthread_mutex_lock(&philo->sim->philo_mutex[r_fork]);
		philo->right_hand = 1;
	}
	ft_log(ft_fork_time(philo), philo, "has taken a fork.");
	if (philo->id == 1)
	{
		pthread_mutex_lock(&philo->sim->philo_mutex[r_fork]);
		philo->right_hand = 1;
	}
	else
	{
		pthread_mutex_lock(&philo->sim->philo_mutex[l_fork]);
		philo->left_hand = 1;
	}
	ft_log(ft_fork_time(philo), philo, "has taken a fork.");
}

long int	ft_fork_time(t_philosopher *philo)
{
	struct timeval	current_time;
	long int		fork_time;

	gettimeofday(&current_time, NULL);
	fork_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	fork_time = fork_time - philo->sim->start_time;
	return (fork_time);
}

void	solo_philo(t_philosopher *philo)
{
	struct timeval	current_time;
	long int		fork_time;

	pthread_mutex_lock(&philo->sim->philo_mutex[0]);
	philo->left_hand = 1;
	ft_log(ft_fork_time(philo), philo, "has taken a fork.");
	usleep(philo->sim->time_to_die * 1000);
	gettimeofday(&current_time, NULL);
	fork_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	fork_time = fork_time - philo->sim->start_time;
	ft_log(fork_time, philo, "died.");
	pthread_mutex_unlock(&philo->sim->philo_mutex[0]);
	philo->left_hand = 0;
	pthread_mutex_lock(&philo->sim->sim_mutex[OFF]);
	philo->sim->sim_on_off = 0;
	release_all_forks(philo->sim);
	pthread_mutex_unlock(&philo->sim->sim_mutex[OFF]);
}

void	error_message(t_simulation *sim)
{
	printf("Philosopher memory allocation failed.\n");
	ft_clean_simulation(sim);
}

void	clean_mutex_meals(t_simulation *sim, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		pthread_mutex_destroy(&sim->philosopher[j].meal);
		j++;
	}
}
