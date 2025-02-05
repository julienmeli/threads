/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 09:32:07 by jmeli             #+#    #+#             */
/*   Updated: 2025/02/05 10:14:49 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clean_all(t_simulation *sim, int i)
{
	clean_mutex_meals(sim, i);
	clean_mutexes(sim, sim->nb_philos);
	ft_clean_simulation(sim);
}

int	all_meals_eaten(t_simulation *sim)
{
	int	i;

	if (sim->nb_meals == -1)
		return (0);
	i = 0;
	while (i < sim->nb_philos)
	{
		pthread_mutex_lock(&sim->philosopher[i].meal);
		if (sim->philosopher[i].meals_eaten < sim->nb_meals)
		{
			pthread_mutex_unlock(&sim->philosopher[i].meal);
			return (0);
		}
		pthread_mutex_unlock(&sim->philosopher[i].meal);
		i++;
	}
	return (1);
}

int	your_number_is_up(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->nb_philos)
	{
		if (!check_hunger(&sim->philosopher[i]))
			return (1);
		i++;
	}
	return (0);
}

void	*function(void *arg)
{
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	while (1)
	{
		if (all_meals_eaten(sim) || your_number_is_up(sim))
		{
			pthread_mutex_lock(&sim->sim_mutex[OFF]);
			sim->sim_on_off = 0;
			pthread_mutex_unlock(&sim->sim_mutex[OFF]);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
