/* *****************************write********************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:09:02 by jmeli             #+#    #+#             */
/*   Updated: 2025/01/22 14:34:53 by jmeli            ###   ########.fr       */
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
	free(sim->philosopher);
	//free(sim);
}

void	instructions(void)
{
	ft_putstr("Usage:\n");
	ft_putstr("./philo <nb_of_guys> <time_to_die (ms)> <to_eat (ms)> <to_sleep (ms)> <nb_of_meals>\n");
	ft_putstr("Nbs of philos and meals must be > 0. Negative time? Ah ah!\n");
}

int	main(int argc, char **argv)
{
	t_simulation	sim;
	
	if (ft_arguments(argc, argv) == 0)
        {
		ft_putstr("Usage:\n");
	       	ft_putstr("./philo <nb_of_guys> <time_to_die (ms)> <to_eat (ms)> <to_sleep (ms)> <nb_of_meals>\n");
        	ft_putstr("Nbs of philos and meals must be > 0.\nNegative time? Ah ah!\n");
		return (1);
        }
	ft_init_simulation(&sim, argc, argv);
	printf("%d\n", sim.nb_philos);
	ft_run_simulation(&sim);
	puts("Here, already?");
	ft_clean_simulation(&sim);
	return (0);
}
