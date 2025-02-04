/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:09:02 by jmeli             #+#    #+#             */
/*   Updated: 2025/02/04 10:54:02 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_clean_simulation(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < NB_SIM_MUTEXES)
	{
		pthread_mutex_destroy(&sim->sim_mutex[i]);
		i++;
	}
	i = 0;
	while (i < sim->nb_philos)
	{
		pthread_mutex_destroy(&sim->philo_mutex[i]);
		i++;
	}
	free(sim->philo_mutex);
	free(sim->philosopher);
}

void	instructions(void)
{
	printf("Usage:\n");
	printf("arg1: nb_of_guys; arg2: time_to_die in ms.");
	printf("arg3: time_to_eat (ms); arg4: time_to_sleep (ms);");
	printf("arg5 (optional): nb_of_meals\n");
	printf("Nbs of philos and meals must be > 0.");
	printf("Negative time is an interesting concept,");
	printf(" but not accepted in this project.");
}

int	main(int argc, char **argv)
{
	t_simulation	sim;

	if (ft_arguments(argc, argv) == 0)
	{
		instructions();
		return (1);
	}
	ft_init_simulation(&sim, argc, argv);
	ft_run_simulation(&sim);
	clean_mutex_meals(&sim, sim.nb_philos);
	ft_clean_simulation(&sim);
	return (0);
}
