/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:02:36 by jmeli             #+#    #+#             */
/*   Updated: 2025/01/30 13:30:57 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long int	ft_fork_time(t_philosopher *philo)
{
	struct timeval	current_time;
	long int		fork_time;

	gettimeofday(&current_time, NULL);
	fork_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	fork_time = fork_time - philo->sim->start_time;
	return (fork_time);
}

int	check_left_fork(t_philosopher *philo)
{
	int	neighbor_id;

	if (philo->id == philo->sim->nb_philos)
		neighbor_id = 1;
	else
		neighbor_id = philo->id + 1;
	if (philo->sim->philosopher[neighbor_id - 1].right_hand == 1)
		return (0);
	else
		return (1);
}

void	solo_philo(t_philosopher *philo)
{
	struct timeval	current_time;
	long int		fork_time;

	usleep(philo->sim->time_to_die * 1000);
	gettimeofday(&current_time, NULL);
	fork_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	fork_time = fork_time - philo->sim->start_time;
	ft_log(fork_time, philo, "died.");
	pthread_mutex_unlock(philo->right_fork);
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
