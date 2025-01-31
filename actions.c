/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:21:28 by jmeli             #+#    #+#             */
/*   Updated: 2025/01/30 13:04:37 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philosopher *philo)
{
	long int		fork_time;

	pthread_mutex_lock(philo->right_fork);
	philo->right_hand = 1;
	fork_time = ft_fork_time(philo);
	if (sudden_death(philo) || philo->sim->sim_on_off == 0)
		return ;
	usleep(1);
	ft_log(fork_time, philo, "has taken a fork.");
	if (philo->sim->nb_philos == 1)
	{
		solo_philo(philo);
		return ;
	}
	while (!check_left_fork(philo))
	{
		if (sudden_death(philo) || philo->sim->sim_on_off == 0)
			return ;
	}
	pthread_mutex_lock(philo->left_fork);
	philo->left_hand = 1;
	fork_time = ft_fork_time(philo);
	if (sudden_death(philo) || philo->sim->sim_on_off == 0)
		return ;
	ft_log(fork_time, philo, "has taken a fork.");
}

void	eat(t_philosopher *philo)
{
	struct timeval	current_time;
	long int		meal_time;

	gettimeofday(&current_time, NULL);
	meal_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	meal_time = meal_time - philo->sim->start_time;
	if (sudden_death(philo) || philo->sim->sim_on_off == 0)
		return ;
	ft_log(meal_time, philo, " is eating.");
	philo->time_of_last_meal = meal_time;
	philo->meals_eaten++;
	check_meals(philo);
	if (philo->sim->time_to_die < philo->sim->time_to_eat)
	{
		usleep(philo->sim->time_to_die * 1000);
		if (sudden_death(philo) || philo->sim->sim_on_off == 0)
			return ;
	}
	if (philo->sim->sim_on_off == 1)
	{
		usleep(philo->sim->time_to_eat * 1000);
	}
}

void	release_forks(t_philosopher *philo)
{
	if (philo->right_hand == 1)
	{
		pthread_mutex_unlock(philo->right_fork);
		philo->right_hand = 0;
	}
	if (philo->left_hand == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		philo->left_hand = 0;
	}
}

void	nap(t_philosopher *philo)
{
	long int		sleep_time;
	int				sand;

	sleep_time = ft_fork_time(philo);
	if (sudden_death(philo) || philo->sim->sim_on_off == 0)
		return ;
	usleep(10);
	ft_log(sleep_time, philo, " is sleeping.");
	if ((philo->sim->time_to_die < (philo->sim->time_to_eat
				+ philo->sim->time_to_sleep))
		|| (philo->sim->time_to_die < philo->sim->time_to_sleep))
	{
		sand = 0;
		while (sand <= philo->sim->time_to_sleep)
		{
			usleep(1000);
			if (sudden_death(philo))
				break ;
			sand = sand + 1;
		}
	}
	else
		usleep(philo->sim->time_to_sleep * 1000);
}

void	think(t_philosopher *philo)
{
	struct timeval	current_time;
	long int		think_time;

	gettimeofday(&current_time, NULL);
	think_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	think_time = think_time - philo->sim->start_time;
	usleep(10);
	ft_log(think_time, philo, " is thinking.");
}
