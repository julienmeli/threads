#include "philosophers.h"

void	take_forks(t_philosopher *philo)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
}

void	eat(t_philosopher *philo)
{
	struct timeval	current_time;
	long int	meal_time;	
	
	gettimeofday(&current_time, NULL);
	meal_time = current_time.tv_sec * 1000000 + current_time.tv_usec;
	meal_time = meal_time - philo->sim.start_time;
	ft_log(meal_time, philo, " is eating.");
	philo->time_of_last_meal = meal_time;
	philo->meals_eaten++;
	usleep(philo->sim.time_to_eat);
}

void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
}

void	sleep(t_philosopher *philo)
{
	struct timeval current_time;
	long int	sleep_time;

	gettimeofday(&current_time, NULL);
	sleep_time = current_time.tv_sec * 1000000 + current_time.tv_usec;
	sleep_time = sleep_time - philo->sim.start_time;
	ft_log(sleep_time, philo, " is sleeping.");
	usleep(philo->sim.time_to_sleep);
}

void	think(t_philosopher *philo)
{
	struct timeval current_time;
        long int        think_time;

        gettimeofday(&current_time, NULL);
        think_time = current_time.tv_sec * 1000000 + current_time.tv_usec;              think_time = think_time - philo->sim.start_time;                                ft_log(think_time, philo, " is thinking.");
        usleep(philo->sim.time_to_sleep);
}
