/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:15:04 by jmeli             #+#    #+#             */
/*   Updated: 2025/02/04 10:55:22 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_hunger(t_philosopher *philosopher)
{
	struct timeval	current_time;
	long int		now;

	gettimeofday(&current_time, NULL);
	now = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	now = now - philosopher->sim->start_time;
	pthread_mutex_lock(&philosopher->meal);
	if ((now * 1000 - philosopher->time_of_last_meal
			* 1000) >= philosopher->sim->time_to_die * 1000)
	{
		ft_log(now, philosopher, "has died.");
		pthread_mutex_unlock(&philosopher->meal);
		return (0);
	}
	pthread_mutex_unlock(&philosopher->meal);
	return (1);
}

void	*eat_prey_love(void *arg)
{
	t_philosopher	*ptr;

	ptr = (t_philosopher *)arg;
	while (simonoff(ptr))
	{
		take_forks(ptr);
		eat(ptr);
		release_forks(ptr);
		nap(ptr);
		think(ptr);
	}
	return (NULL);
}

void	*eat_prey_love_odd(void *arg)
{
	t_philosopher	*ptr;

	ptr = (t_philosopher *)arg;
	while (simonoff(ptr))
	{
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

	pthread_create(&sim->process, NULL, &function, sim);
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
	pthread_join(sim->process, NULL);
}
