#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

#include <stdio.h>

#define NB_SIM_MUTEXES 5

typedef enum	t_sim_mutexes
{
	HUNGER,
	MEALS,
	TIME,
	OFF,
	LOG
}		t_sim_mutexes;

typedef struct  s_philosopher
{
        struct s_simulation     *sim;
        int             id;
        int             meals_eaten;
        long int        time_of_last_meal;
        pthread_t       thread;
        pthread_mutex_t *left_fork;
	int		left_hand;
        pthread_mutex_t *right_fork;
	int		right_hand;
}               t_philosopher;

typedef struct	s_simulation
{
	int	nb_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_meals;
	int	sim_on_off;
	long int	start_time;
	pthread_mutex_t	*philo_mutex;
	t_philosopher	*philosopher;
	pthread_mutex_t sim_mutex[NB_SIM_MUTEXES];
}		t_simulation;

//actions.c
void    take_forks(t_philosopher *philo);
void    eat(t_philosopher *philo);
void    release_forks(t_philosopher *philo);
void    nap(t_philosopher *philo);
void    think(t_philosopher *philo);

//arguments.c
int     ft_atoi(char *str);
int     ft_arguments(int argc, char **argv);

//diary.c
void    ft_putstr(char *str);
void    ft_putnbr(unsigned long int nb);
int     simonoff(t_philosopher *philo);
int     sudden_death(t_philosopher *philo);
void    ft_log(long int time, t_philosopher *philo, char *str);

//initialization.c
void    ft_init_simulation(t_simulation *sim, int argc, char **argv);

//main.c
void    ft_clean_simulation(t_simulation *sim);

//running.c
int     check_hunger(t_philosopher *philosopher);
int     check_meals(t_philosopher *philosopher);
void    ft_run_simulation(t_simulation *sim);

#endif
