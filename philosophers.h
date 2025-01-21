#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct	s_simulation
{
	int	nb_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_meals;
	long int	start_time;
	pthread_mutex_t	sim_mutex[3];
	pthread_mutex_t	*philo_mutex;
	t_philosopher	*philosopher;
}		t_simulation;

typedef struct	s_philosopher
{
	struct s_simulation	*sim;
	int		id;
	int		meals_eaten;
	long int	time_of_last_meal;
	pthread_t	thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}		t_philosopher;

#endif
