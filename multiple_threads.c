#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	*print_thread_id(void *arg)
{
	int	thread_index;

	thread_index = *(int *)arg;
	printf("Philosopher %d\n", thread_index);
	free(arg);
	return (NULL);
}

int	main(int argc, char **argv)
{
	int	num_threads;
	int	i;
	int	*thread_index;
	pthread_t	*threads;
	
	if (argc == 2)
	{
	num_threads = atoi(argv[1]);
	threads = malloc(num_threads * sizeof(threads));
	i = 0;
	while (i < num_threads)
	{
		sleep(0.5);
		thread_index = malloc(sizeof(int));
		if (pthread_create(&threads[i], NULL, print_thread_id, thread_index) != 0)
		{
			perror("Failed to create thread");
			return (1);
		}
		//sleep(0.5);
		*thread_index = i;
		i++;
	}
	i = 0;
	while (i < num_threads)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
	printf("All threads have completed.\n");
	}
	return (0);
}	
