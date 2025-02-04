/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:23:31 by jmeli             #+#    #+#             */
/*   Updated: 2025/02/04 11:50:55 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define NB_SIM_MUTEXES 2

typedef enum t_sim_mutexes
{
	OFF,
	LOG
}						t_sim_mutexes;

typedef struct s_philosopher
{
	struct s_simulation	*sim;
	int					id;
	int					meals_eaten;
	long int			time_of_last_meal;
	pthread_t			thread;
	int					left_hand;
	pthread_mutex_t		meal;
	int					right_hand;
}						t_philosopher;

typedef struct s_simulation
{
	int					nb_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_meals;
	int					sim_on_off;
	long int			start_time;
	pthread_t			process;
	pthread_mutex_t		*philo_mutex;
	t_philosopher		*philosopher;
	pthread_mutex_t		sim_mutex[NB_SIM_MUTEXES];
}						t_simulation;

// actions.c
void					take_forks(t_philosopher *philo);
void					eat(t_philosopher *philo);
void					release_forks(t_philosopher *philo);
void					nap(t_philosopher *philo);
void					think(t_philosopher *philo);

// arguments.c
int						ft_atoi(char *str);
int						ft_arguments(int argc, char **argv);

// diary.c
void					ft_putstr(char *str);
void					ft_putnbr(unsigned long int nb);
int						simonoff(t_philosopher *philo);
void					release_all_forks(t_simulation *sim);
void					ft_log(long int time, t_philosopher *philo, char *str);

// process.c
void					clean_all(t_simulation *sim, int i);
void					*function(void *arg);

// initialization.c
void					clean_mutexes(t_simulation *sim, int index);
void					ft_init_simulation(t_simulation *sim, int argc,
							char **argv);

// main.c
void					ft_clean_simulation(t_simulation *sim);

// running.c
int						check_hunger(t_philosopher *philosopher);
void					ft_run_simulation(t_simulation *sim);

// utils.c
void					left_right_fork(t_philosopher *philo, int l_fork,
							int r_fork);
long int				ft_fork_time(t_philosopher *philo);
void					solo_philo(t_philosopher *philo);
void					error_message(t_simulation *sim);
void					clean_mutex_meals(t_simulation *sim, int i);

#endif
