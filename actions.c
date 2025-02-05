/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:21:28 by jmeli             #+#    #+#             */
/*   Updated: 2025/02/05 11:50:03 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philosopher *philo)
{
	int			r_fork;
	int			l_fork;

	if (philo->id == 1)
	{
		r_fork = philo->sim->nb_philos - 1;
		l_fork = 0;
	}
	else
	{
		r_fork = philo->id - 2;
		l_fork = philo->id - 1;
	}
	if (philo->sim->nb_philos == 1)
	{
		solo_philo(philo);
		return ;
	}
	left_right_fork(philo, l_fork, r_fork);
}

void	eat(t_philosopher *philo)
{
	struct timeval	current_time;
	long int		meal_time;

	gettimeofday(&current_time, NULL);
	meal_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	meal_time = meal_time - philo->sim->start_time;
	ft_log(meal_time, philo, " is eating.");
	pthread_mutex_lock(&philo->meal);
	philo->time_of_last_meal = meal_time;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal);
	if (all_meals_eaten(philo->sim))
		return ;
	if (simonoff(philo))
	{
		usleep(philo->sim->time_to_eat * 1000);
	}
}

void	release_forks(t_philosopher *philo)
{
	int	r_fork;
	int	l_fork;

	if (philo->id == 1)
	{
		r_fork = philo->sim->nb_philos - 1;
		l_fork = 0;
	}
	else
	{
		r_fork = philo->id - 2;
		l_fork = philo->id - 1;
	}
	if (philo->right_hand == 1)
	{
		pthread_mutex_unlock(&philo->sim->philo_mutex[r_fork]);
		philo->right_hand = 0;
	}
	if (philo->left_hand == 1)
	{
		pthread_mutex_unlock(&philo->sim->philo_mutex[l_fork]);
		philo->left_hand = 0;
	}
}

void	nap(t_philosopher *philo)
{
	long int	sleep_time;

	sleep_time = ft_fork_time(philo);
	usleep(100);
	if (all_meals_eaten(philo->sim))
		return ;
	ft_log(sleep_time, philo, " is sleeping.");
	usleep(philo->sim->time_to_sleep * 1000);
}

void	think(t_philosopher *philo)
{
	struct timeval	current_time;
	long int		think_time;

	gettimeofday(&current_time, NULL);
	think_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	think_time = think_time - philo->sim->start_time;
	usleep(100);
	ft_log(think_time, philo, " is thinking.");
}
