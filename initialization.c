/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 08:08:40 by jmeli             #+#    #+#             */
/*   Updated: 2025/01/22 14:41:30 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_mutex(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < NB_SIM_MUTEXES)
	{
		if ((pthread_mutex_init(&sim->sim_mutex[i], NULL)) != 0)
		{
			printf("Sim mutex initialization failed.\n");
			exit(1);
		}
		i++;
	}
}

void	init_philo_mutex(t_simulation *sim)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	sim->philo_mutex = malloc(sim->nb_philos * sizeof(pthread_mutex_t));
	//printf("Beginning of init_philo_mutex i:%d, nb of philos: %d\n", i, sim->nb_philos);
	while (i < sim->nb_philos)
	{
		
		ret = pthread_mutex_init(&sim->philo_mutex[i], NULL);
		if (ret != 0)
		{
			printf("Philo mutex initialization failed.\n");
                        exit(1);
		}
		i++;
	}
}

void	init_philosophers(t_simulation *sim)
{
	int	i;

	sim->philosopher = malloc(sim->nb_philos * sizeof(t_philosopher));
	if (!sim->philosopher)
	{
		printf("Philosopher memory allocation failed.\n");
		exit(1);
	}
	i = 0;
	while (i < sim->nb_philos)
	{
		sim->philosopher[i].sim = sim;
		sim->philosopher[i].id = i + 1;
		sim->philosopher[i].meals_eaten = 0;
		sim->philosopher[i].time_of_last_meal = sim->start_time;
		sim->philosopher[i].left_hand = 0;
		sim->philosopher[i].right_hand = 0;
		sim->philosopher[i].left_fork = &sim->philo_mutex[i];
		if (i == 0)
			sim->philosopher[i].right_fork = &sim->philo_mutex[sim->nb_philos - 1];
		else
			sim->philosopher[i].right_fork = &sim->philo_mutex[i - 1];
		i++;
	}
}

void	ft_init_simulation(t_simulation *sim, int argc, char **argv)
{
	struct timeval	initial_time;
	
	(void)argc;
	sim->nb_philos = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		sim->nb_meals = ft_atoi(argv[5]);
	else
		sim->nb_meals = -1;
	sim->sim_on_off = 1;
	gettimeofday(&initial_time, NULL);
	sim->start_time = initial_time.tv_sec * 1000 + initial_time.tv_usec / 1000;
	//printf("start_time:%ld\n", sim->start_time);
	init_mutex(sim);
	//puts("After init_mutex");
	init_philo_mutex(sim);
	//puts("After init_philo_mutex");
	init_philosophers(sim);
}
