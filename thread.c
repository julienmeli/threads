#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

void	ft_time_stamp(int nb, int counter) 
{
    time_t current_time;
    struct tm *time_info;
    char time_string[100]; // Buffer for formatted time
	char	*str;

	if (nb == 1)
		str = "my_func";
	else
		str = "other_func";

    // Get the current time
    current_time = time(NULL);

    // Convert to local time
    time_info = localtime(&current_time);

    // Format time as "YYYY-MM-DD HH:MM:SS"
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", time_info);

    // Display the timestamp
    printf("Current Timestamp: %s %s %d\n", time_string, str, counter);
}

void	*my_func(void *arg)
{	
	int	i;
	int	*time;
	
	time = (int *)arg;
	i = 0;
	while (i < 10)
	{
		ft_time_stamp(1, *time);
		(*time)++;
		sleep(1);
		i++;
	}
	return (NULL);
}

void	other_func(void)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		ft_time_stamp(2, 0);
                sleep(2);
                i++;
	}
}

int	main(void)
{
	pthread_t	new_thread;
	int		t; //lapsed_time_to_pass_relay;
	
	t = 1;
	pthread_create(&new_thread, NULL, &my_func, &t);
       	other_func();
	pthread_join(new_thread, NULL);
	printf("Finished! %d\n", t);
	return (0);	
}
