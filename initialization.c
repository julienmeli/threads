#include "philosophers.h"

void	init_mutex(t_simulation *sim)
{
	sim->sim_mutex[3] = malloc(3 * sizeof(pthread_mutex_t));
        if (!sim->sim_mutex)
        {
                error_message;
                exit(1);
        }
	pthread_mutex_init(&sim->sim_mutex[0], NULL);
	pthread_mutex_init(&sim->sim_mutex[1], NULL);
	pthread_mutex_init(&sim->sim_mutex[2], NULL);
}

void	init_philo_mutex(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->philo_mutex = malloc(ft_atoi(argv[1]) * sizeof(pthread_mutex_t));
	if (!sim->philo_mutex)
	{
		error_message;
		exit(1);
	}
	while (i < sim->nb_philos)
	{
		pthread_mutex_init(&sim->philo_mutex[i], NULL);
		i++;
	}
}

void	init_philosophers(t_simulation *sim)
{
	int	i;

	sim->philosopher = malloc(nb_philos * sizeof(t_philosopher));
	if (!sim->philosopher)
	{
		error_message;
		exit(1);
	}
	i = 0;
	while (i < sim->nb_philos)
	{
		sim->philosopher[i].sim = sim;
		sim->philosopher[i].id = id + 1;
		sim->philosopher[i].meals_eaten = 0;
		sim->philosopher[i].time_of_last_meal = sim->start_time;
		sim->philosopher[i].left_fork = &sim->philo_mutex[i];
		if (i == 0)
			sim->philosopher[i].right_fork = &sim->philo_mutex[sim->nb_philos - 1];
		else
			sim->philosopher[i].right_fork = &sim->philo_mutex[i - 1];
	}
}

void	ft_init_simulation(t_simulation *sim, int argc, char **argv)
{
	struct timeval	initial_time;

	sim->nb_philos = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	gettimeofday(&initial_time, NULL);
	sim->start_time = initial_time.tv_sec * 1000000 + initial_time.tv_usec;
	init_mutex(sim);
	init_philo_mutex(sim);
	init_philosophers(sim);
}
