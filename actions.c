/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:21:28 by jmeli             #+#    #+#             */
/*   Updated: 2025/01/22 14:50:05 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philosopher *philo)
{
	struct timeval	current_time;
	long int	fork_time;

	pthread_mutex_lock(philo->right_fork);
	if (philo->id % 2 == 1)
		usleep(2000);
	else
		usleep(1000);	
	gettimeofday(&current_time, NULL);
        fork_time = current_time.tv_sec * 1000 + current_time.tv_usec/1000;
	printf("fork_time: %ld start_time: %ld\n", fork_time, philo->sim->start_time);
        fork_time = fork_time - philo->sim->start_time;
	ft_log(fork_time, philo, " has taken a fork.");
	pthread_mutex_lock(philo->left_fork);
	gettimeofday(&current_time, NULL);
        fork_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
        fork_time = fork_time - philo->sim->start_time;
	ft_log(fork_time, philo, " has taken a fork.");
}

void	eat(t_philosopher *philo)
{
	struct timeval	current_time;
	long int	meal_time;	
	
	gettimeofday(&current_time, NULL);
	meal_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	printf("meal_time: %ld start_time: %ld\n", meal_time, philo->sim->start_time);
	meal_time = meal_time - philo->sim->start_time;
	ft_log(meal_time, philo, " is eating.");
	philo->time_of_last_meal = meal_time;
	philo->meals_eaten++;
	check_meals(philo);
	usleep(philo->sim->time_to_eat * 1000);
}

void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
}

void	nap(t_philosopher *philo)
{
	struct timeval current_time;
	long int	sleep_time;

	gettimeofday(&current_time, NULL);
	sleep_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	printf("sleep_time: %ld start_time: %ld\n", sleep_time, philo->sim->start_time);
	sleep_time = sleep_time - philo->sim->start_time;
	ft_log(sleep_time, philo, " is sleeping.");
	usleep(philo->sim->time_to_sleep * 1000);
}

void	think(t_philosopher *philo)
{
	struct timeval current_time;
        long int        think_time;

        gettimeofday(&current_time, NULL);
        think_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	printf("think_time: %ld start_time: %ld\n", think_time, philo->sim->start_time);
	think_time = think_time - philo->sim->start_time;
	ft_log(think_time, philo, " is thinking.");
        usleep(philo->sim->time_to_sleep * 1000);
}
