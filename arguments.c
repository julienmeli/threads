#include "philosophers.h"

int	ft_atoi(char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' || *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * sign);
}

int	ft_arguments(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (0);
	else if (ft_atoi(argv[1] == 0))
		return (0);
	else if (argv[6] && ft_atoi(argv[6] == 0))
		return (0);
	else
		return (1);
}
