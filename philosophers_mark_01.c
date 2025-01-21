#include <pthread.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_simulation	sim;
	
	sim = malloc(sizeof(t_simulation));
	if (!sim)
	{
		error_message;
		return (1);
	}
	if (!ft_arguments(argc, argv))
	{
		error_message;
		return (1);
	}
	ft_init_simulation(&sim, argc, argv);;
	ft_run_simulation(&sim);
	ft_clean_simulation(&sim);
	return (0);
}
