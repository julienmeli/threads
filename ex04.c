#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define NB_ITER 42

typedef struct	s_thread
{
	int		var;
	pthread_mutex_t	lock;
}		t_thread;

void	*increment(void *arg)
{
	t_thread	*ptr;
	int	i;

	i = 0;
	ptr = (t_thread *)arg;
	while (i < NB_ITER)
	{
		pthread_mutex_lock(&ptr->lock);
		ptr->var++;
		printf("%d\n", ptr->var);
		pthread_mutex_unlock(&ptr->lock);
		i++;
		usleep(10000);
	}
	return (NULL);
}

void	*decrement(void *arg)
{
	t_thread	*ptr;
	int	j;
	
	j = 0;
	ptr = (t_thread *)arg;
	while (j < NB_ITER)
	{
		pthread_mutex_lock(&ptr->lock);
		ptr->var--;
		printf("%d\n", ptr->var);
		pthread_mutex_unlock(&ptr->lock);
		j++;
		usleep(10000);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	new_thread;
	pthread_t	new_thread2;
	struct s_thread	fil;
	
	fil.var = 0;
	pthread_mutex_init(&fil.lock, NULL);
	pthread_create(&new_thread, NULL, increment, &fil);
	pthread_create(&new_thread2, NULL, decrement, &fil);
	pthread_join(new_thread, NULL);
	pthread_join(new_thread2, NULL);
	pthread_mutex_destroy(&fil.lock);
	printf("Final var %d\n", fil.var);
	return (0);
}
