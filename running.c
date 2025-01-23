/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:15:04 by jmeli             #+#    #+#             */
/*   Updated: 2025/01/22 14:41:01 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_hunger(t_philosopher *philosopher)
{
	struct timeval	current_time;
	long int	now;
	
	gettimeofday(&current_time, NULL);
	now = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	now = now - philosopher->sim->start_time;
	printf("In check_hunger, now: %ld time of last meal: %ld time to die: %d\n", now, philosopher->time_of_last_meal, philosopher->sim->time_to_die);
	if ((now * 1000 - philosopher->time_of_last_meal * 1000) >= philosopher->sim->time_to_die * 1000)
	{
		ft_log(now, philosopher, "has died.");
		exit(0);
	}
	return (1);
}

int	check_meals(t_philosopher *philosopher)
{
	printf("id: %d, meals_eatern: %d, nb_meals: %d\n", philosopher->id, philosopher->meals_eaten, philosopher->sim->nb_meals);
	if (philosopher->meals_eaten >= philosopher->sim->nb_meals)
	{
		exit(0);
	}
	return (1);
}

void	*eat_prey_love(void *arg)
{
	t_philosopher	*ptr;

	ptr = (t_philosopher *)arg;
	//puts("check eat prey love");
	//printf("check_meals%d check_hunger%d\n", check_meals(ptr), check_hunger(ptr));
	while (check_meals(ptr) && check_hunger(ptr))
	{
		//printf("Before take_forks %d\n", ptr->id);
		take_forks(ptr);
		//printf("after take_forks %d\n", ptr->id);
		eat(ptr);
		release_forks(ptr);
		nap(ptr);
		think(ptr);
	}
	return (NULL);
}

void    create_philo_threads(t_simulation *sim)
{
        int     i;

        i = 0;
	printf("check: %d\n", sim->philosopher[8].id);
        while (i < sim->nb_philos)
        {
                pthread_create(&sim->philosopher[i].thread, NULL, &eat_prey_love, &sim->philosopher[i]);
		/*if (philosopher[i].id % 2 == 1)
		{
			usleep(1000);
		}*/
                //printf("nb_philos:%d i:%d\n", sim->nb_philos, i);
		i++;
        }
	puts("end of create philo threads");
}

void	ft_run_simulation(t_simulation *sim)
{
	int	i;

	create_philo_threads(sim);
	i = 0;
	while (i < sim->nb_philos)
        {
                pthread_join(sim->philosopher[i].thread, NULL);
                i++;
        }
}
