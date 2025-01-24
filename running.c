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
	
	pthread_mutex_lock(&philosopher->sim->sim_mutex[HUNGER]);
	gettimeofday(&current_time, NULL);
	now = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	now = now - philosopher->sim->start_time;
	//printf("In check_hunger, now: %ld time of last meal: %ld time to die: %d\n", now, philosopher->time_of_last_meal, philosopher->sim->time_to_die);
	if ((now * 1000 - philosopher->time_of_last_meal * 1000) >= philosopher->sim->time_to_die * 1000)
	{
		ft_log(now, philosopher, "has died.");
		philosopher->sim->sim_on_off = 0;
		pthread_mutex_unlock(&philosopher->sim->sim_mutex[HUNGER]);
		//ft_clean_simulation(philosopher->sim);
		return (0);
	}
	pthread_mutex_unlock(&philosopher->sim->sim_mutex[HUNGER]);
	return (1);
}

int	check_meals(t_philosopher *philosopher)
{
	//printf("id: %d, meals_eatern: %d, nb_meals: %d\n", philosopher->id, philosopher->meals_eaten, philosopher->sim->nb_meals);
	pthread_mutex_lock(&philosopher->sim->sim_mutex[MEALS]);
	if (philosopher->meals_eaten >= philosopher->sim->nb_meals)
	{
		//ft_clean_simulation(philosopher->sim);
		philosopher->sim->sim_on_off = 0;
		pthread_mutex_unlock(&philosopher->sim->sim_mutex[MEALS]);
		return (0);
	}
	pthread_mutex_unlock(&philosopher->sim->sim_mutex[MEALS]);
	return (1);
}

void	doublecheck(t_philosopher *philosopher)
{
	if (!check_meals(philosopher) || !check_hunger(philosopher))
	{
		philosopher->sim->sim_on_off = 0;
	}
}

void	*eat_prey_love(void *arg)
{
	t_philosopher	*ptr;

	ptr = (t_philosopher *)arg;
	//puts("check eat prey love");
	//printf("check_meals%d check_hunger%d\n", check_meals(ptr), check_hunger(ptr));
	while (check_meals(ptr) && check_hunger(ptr) && ptr->sim->sim_on_off == 1)
	{
		//printf("Before take_forks %d\n", ptr->id);
		//doublecheck(ptr);
		if (ptr->sim->sim_on_off == 0)
			break;
		take_forks(ptr);
		if (ptr->sim->sim_on_off == 0)
                        break;
		//printf("after take_forks %d\n", ptr->id);
		eat(ptr);
		if (ptr->sim->sim_on_off == 0)
                        break;
		//puts("checking");
		release_forks(ptr);
		if (ptr->sim->sim_on_off == 0)
                        break;
		nap(ptr);
		if (ptr->sim->sim_on_off == 0)
                        break;
		think(ptr);
		if (ptr->sim->sim_on_off == 0)
                        break;
		//printf("id: %d nb of meals: %d\n", ptr->id, ptr->meals_eaten);
	}
	//printf("id: %d last check?\n", ptr->id);
	return (NULL);
}

void    create_philo_threads(t_simulation *sim)
{
        int     i;

        i = 0;
	//printf("check: %d\n", sim->philosopher[8].id);
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
	//puts("end of create philo threads");
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
	//puts("check at the end of ft_run_simulation");
}
