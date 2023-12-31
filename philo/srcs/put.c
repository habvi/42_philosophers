#include "philo.h"
#include "utils.h"
#include <stdio.h> // printf
#include <unistd.h>

// call in lock
void	put_log(const t_philo *philo, const char *message)
{
	const int64_t	elapsed_time = \
					(philo->current_time - philo->start_time_of_philo) / 1000;

	if (ft_streq(message, MSG_EAT))
		printf(PINK SPEC_I64" %d %s\n"END, elapsed_time, philo->id, message);
	else if (ft_streq(message, MSG_SLEEP))
		printf(BLUE SPEC_I64" %d %s\n"END, elapsed_time, philo->id, message);
	else if (ft_streq(message, MSG_THINK))
		printf(GREEN SPEC_I64" %d %s\n"END, elapsed_time, philo->id, message);
	else if (ft_streq(message, MSG_DIED))
		printf(RED SPEC_I64" %d %s\n"END, elapsed_time, philo->id, message);
	else
		printf(SPEC_I64" %d %s\n", elapsed_time, philo->id, message);
}

// call in lock
// set philo->current_time in is_simulation_over()
// set_time() is only used eating
int64_t	put_log_flow(t_philo *philo, void (*set_time)(), const char *message)
{
	if (is_simulation_over(philo))
		return (FAILURE);
	if (set_time != NULL)
		set_time(philo, philo->current_time);
	put_log(philo, message);
	return (SUCCESS);
}

int	put_error(const char *message)
{
	if (ft_putstr_fd("Error: ", STDERR_FILENO) == WRITE_ERROR)
		return (EXIT_FAILURE);
	if (ft_putstr_fd(message, STDERR_FILENO) == WRITE_ERROR)
		return (EXIT_FAILURE);
	if (ft_putstr_fd("\n", STDERR_FILENO) == WRITE_ERROR)
		return (EXIT_FAILURE);
	return (EXIT_FAILURE);
}
