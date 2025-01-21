#include "philosophers.h"

int	check_hunger(t_philosopher *philosopher)
{
	struct timeval	current_time;
	long int	now;
	
	gettimeofday(&current_time, NULL);
	now = current_time.tv_sec * 1000000 + current_time.tv_usec;
	if ((now - philosopher.time_of_last_meal) >= time_to_die)
	{
		ft_log(now, philosopher, "has died.");
		exit(0);
	}
}

void	*eat_prey_love(void *arg)
{
	t_philosopher	*ptr;

	ptr = (t_philosopher *)arg;
	if (!sim)
	{
		error_message;
		exit(1);
	}
	if (!check_meals(ptr) && !check_hunger(ptr))
	{
		take_forks(ptr);
		eat(ptr);
		release_forks(ptr);
		sleep(ptr);
		think(ptr);
	}
	return (NULL);
}

void    create_philo_threads(t_simulation *sim)
{
        int     i;

        i = 0;
        while (i < sim->nb_philos)
        {
                pthread_create(&sim->philosopher[i].thread, NULL, eat_prey_love, &sim->philosopher[i]);
                i++;
        }
}

void	running(t_simulation *sim)
{
	create_philo_threads(sim);
	join_philo_threads(sim);
}
