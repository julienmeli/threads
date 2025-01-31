/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:15:04 by jmeli             #+#    #+#             */
/*   Updated: 2025/01/30 13:29:17 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_hunger(t_philosopher *philosopher)
{
	struct timeval	current_time;
	long int		now;

	pthread_mutex_lock(&philosopher->sim->sim_mutex[HUNGER]);
	gettimeofday(&current_time, NULL);
	now = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	now = now - philosopher->sim->start_time;
	if ((now * 1000 - philosopher->time_of_last_meal
			* 1000) >= philosopher->sim->time_to_die * 1000)
	{
		ft_log(now, philosopher, "has died.");
		pthread_mutex_lock(&philosopher->sim->sim_mutex[OFF]);
		philosopher->sim->sim_on_off = 0;
		release_all_forks(philosopher->sim);
		pthread_mutex_unlock(&philosopher->sim->sim_mutex[OFF]);
		pthread_mutex_unlock(&philosopher->sim->sim_mutex[HUNGER]);
		return (0);
	}
	pthread_mutex_unlock(&philosopher->sim->sim_mutex[HUNGER]);
	return (1);
}

int	check_meals(t_philosopher *philo)
{
	int	i;

	pthread_mutex_lock(&philo->sim->sim_mutex[MEALS]);
	if ((philo->sim->nb_meals > 0)
		&& (philo->meals_eaten >= philo->sim->nb_meals))
	{
		i = 0;
		while (i < philo->sim->nb_philos)
		{
			if (philo->sim->philosopher[i].meals_eaten < philo->sim->nb_meals)
			{
				pthread_mutex_unlock(&philo->sim->sim_mutex[MEALS]);
				return (1);
			}
			i++;
		}
		pthread_mutex_lock(&philo->sim->sim_mutex[OFF]);
		philo->sim->sim_on_off = 0;
		release_all_forks(philo->sim);
		pthread_mutex_unlock(&philo->sim->sim_mutex[OFF]);
		pthread_mutex_unlock(&philo->sim->sim_mutex[MEALS]);
		return (0);
	}
	pthread_mutex_unlock(&philo->sim->sim_mutex[MEALS]);
	return (1);
}

void	*eat_prey_love(void *arg)
{
	t_philosopher	*ptr;

	ptr = (t_philosopher *)arg;
	while (check_meals(ptr) && check_hunger(ptr) && ptr->sim->sim_on_off == 1)
	{
		if (simonoff(ptr) == 0)
			break ;
		take_forks(ptr);
		if (simonoff(ptr) == 0)
			break ;
		eat(ptr);
		if (simonoff(ptr) == 0)
			break ;
		release_forks(ptr);
		if (simonoff(ptr) == 0)
			break ;
		nap(ptr);
		if (simonoff(ptr) == 0)
			break ;
		think(ptr);
		if (simonoff(ptr) == 0)
			break ;
	}
	return (NULL);
}

void	*eat_prey_love_odd(void *arg)
{
	t_philosopher	*ptr;

	ptr = (t_philosopher *)arg;
	while (check_meals(ptr) && check_hunger(ptr) && ptr->sim->sim_on_off == 1)
	{
		if (simonoff(ptr) == 0)
			break ;
		if ((ptr->id == ptr->sim->nb_philos) && (ptr->sim->nb_philos > 1))
		{
			nap(ptr);
			think(ptr);
		}
		else
		{
			usleep(2000 * (1 + (ptr->sim->nb_philos / 3)));
			think(ptr);
		}
		eat_prey_love(ptr);
	}
	return (NULL);
}

void	ft_run_simulation(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->nb_philos)
	{
		if (sim->philosopher[i].id % 2 == 1)
			pthread_create(&sim->philosopher[i].thread, NULL,
				&eat_prey_love_odd, &sim->philosopher[i]);
		else
			pthread_create(&sim->philosopher[i].thread, NULL, &eat_prey_love,
				&sim->philosopher[i]);
		i++;
	}
	i = 0;
	while (i < sim->nb_philos)
	{
		pthread_join(sim->philosopher[i].thread, NULL);
		i++;
	}
}
