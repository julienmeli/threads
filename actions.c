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

void	take_forks(t_philosopher *philo)
{
	struct timeval	current_time;
	long int	fork_time;
	
	pthread_mutex_lock(philo->right_fork);	
	philo->right_hand = 1;
	gettimeofday(&current_time, NULL);
        fork_time = current_time.tv_sec * 1000 + current_time.tv_usec/1000;
	//printf("fork_time: %ld start_time: %ld\n", fork_time, philo->sim->start_time);
        fork_time = fork_time - philo->sim->start_time;
	if (sudden_death(philo) || philo->sim->sim_on_off == 0)
		return ;
	usleep(1);
	ft_log(fork_time, philo, "has taken a fork.");
	if (philo->sim->nb_philos == 1)
	{
		//pthread_mutex_lock(&philo->sim->sim_mutex[TIME]);
		usleep(philo->sim->time_to_die * 1000);
		//pthread_mutex_unlock(&philo->sim->sim_mutex[TIME]);
		gettimeofday(&current_time, NULL);
		fork_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
        	fork_time = fork_time - philo->sim->start_time;
		ft_log(fork_time, philo, "died.");
		pthread_mutex_unlock(philo->right_fork);
		//ft_clean_simulation(philo->sim);
		pthread_mutex_lock(&philo->sim->sim_mutex[OFF]);
		philo->sim->sim_on_off = 0;
		release_all_forks(philo->sim);
		pthread_mutex_unlock(&philo->sim->sim_mutex[OFF]);
		return ;
	}
	while (!check_left_fork(philo))
	{
                sudden_death(philo);
	}
	pthread_mutex_lock(philo->left_fork);
	philo->left_hand = 1;
	gettimeofday(&current_time, NULL);
        fork_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
        fork_time = fork_time - philo->sim->start_time;
	if (sudden_death(philo) || philo->sim->sim_on_off == 0)
                return ;
	ft_log(fork_time, philo, "has taken a fork.");
}

void	eat(t_philosopher *philo)
{
	struct timeval	current_time;
	long int	meal_time;	
	
	gettimeofday(&current_time, NULL);
	meal_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	//printf("meal_time: %ld start_time: %ld\n", meal_time, philo->sim->start_time);
	meal_time = meal_time - philo->sim->start_time;
	if (sudden_death(philo) || philo->sim->sim_on_off == 0)
                return ;
	ft_log(meal_time, philo, " is eating.");
	philo->time_of_last_meal = meal_time;
	philo->meals_eaten++;
	//puts("post check");
	check_meals(philo);
	//puts("last check");
	//printf("time to die:%d time to eat:%d\n", philo->sim->time_to_die, philo->sim->time_to_eat);
	if (philo->sim->time_to_die < philo->sim->time_to_eat)
	{
		//printf("get here? id: %d\n", philo->id);
		//pthread_mutex_lock(&philo->sim->sim_mutex[TIME]);
		usleep(philo->sim->time_to_die * 1000);
		//pthread_mutex_unlock(&philo->sim->sim_mutex[TIME]);
		if (sudden_death(philo) || philo->sim->sim_on_off == 0)
                	return ;
	}
	if (philo->sim->sim_on_off == 1)
	{
		//pthread_mutex_lock(&philo->sim->sim_mutex[TIME]);
		usleep(philo->sim->time_to_eat * 1000);
		//pthread_mutex_unlock(&philo->sim->sim_mutex[TIME]);
	}
	//puts("check ?");
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

/*
//Below function to copy and paste in a separate file
void	death_becomes_her(t_philosopher *philo)
{
	struct timeval	current_time;
	long int	now_time;
	long int	countdown;
	if (philo->sim->time_to_sleep + philo->sim->time_to_eat > philo->sim->time_to_die)
	{
		gettimeofday(&current_time, NULL);
        	now_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
        	now_time = now_time - philo->time_of_last_meal;
		countdown = philo->sim->time_to_die * 1000 + philo->time_of_last_meal;
		printf("countdown: %ld\n", countdown);
		while (now_time < countdown)
		{
			gettimeofday(&current_time, NULL);
                	now_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
                	now_time = now_time - philo->time_of_last_meal;
		}
		sudden_death(philo);
	}
}
*/

void	nap(t_philosopher *philo)
{
	struct timeval current_time;
	long int	sleep_time;
	int		sand;

	gettimeofday(&current_time, NULL);
	sleep_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	//printf("sleep_time: %ld start_time: %ld\n", sleep_time, philo->sim->start_time);
	sleep_time = sleep_time - philo->sim->start_time;
	if (sudden_death(philo) || philo->sim->sim_on_off == 0)
                return ;
	usleep(1);
	ft_log(sleep_time, philo, " is sleeping.");
	//death_becomes_her(philo);
	//pthread_mutex_lock(&philo->sim->sim_mutex[TIME]);
	sand = 0;
	while (sand <= philo->sim->time_to_sleep)
	{
		usleep(1000);
		sudden_death(philo);
		sand = sand + 1;
	}
	//pthread_mutex_unlock(&philo->sim->sim_mutex[TIME]);
}

void	think(t_philosopher *philo)
{
	struct timeval current_time;
        long int        think_time;

        gettimeofday(&current_time, NULL);
        think_time = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	//printf("think_time: %ld start_time: %ld\n", think_time, philo->sim->start_time);
	think_time = think_time - philo->sim->start_time;
	if (sudden_death(philo) || philo->sim->sim_on_off == 0)
                return ;
	ft_log(think_time, philo, " is thinking.");
	//pthread_mutex_lock(&philo->sim->sim_mutex[TIME]);
        //usleep(philo->sim->time_to_sleep * 1000);
	//pthread_mutex_unlock(&philo->sim->sim_mutex[TIME]);
}
