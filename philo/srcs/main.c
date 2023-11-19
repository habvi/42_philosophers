#include "philo.h"

static t_result	run_philosophers(\
							t_philo *philos, const unsigned int num_of_philos)
{
	t_shared	shared;
	t_result	result;

	if (init_shared(philos, &shared, num_of_philos) == FAILURE)
		return (error_fatal());
	result = simulate_philos_cycle(philos, &shared, num_of_philos);
	if (result == FAILURE)
		return (error_fatal());
	result = monitoring_death(philos, &shared, num_of_philos);
	if (result == FAILURE)
		return (error_fatal());
	destroy_shared(&shared, num_of_philos);
	return (SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_args		args;
	t_result	result;
	t_philo		*philos;

	if (!is_valid_argc(argc))
		return (EXIT_FAILURE);
	args = set_args(argc, (const char **)argv, &result);
	if (result == FAILURE)
		return (EXIT_FAILURE);
	philos = init_philos(&args);
	if (philos == NULL)
		return (EXIT_FAILURE);
	result = run_philosophers(philos, args.num_of_philos);
	if (result == FAILURE)
	{
		destroy_philos(&philos);
		return (EXIT_FAILURE);
	}
	destroy_philos(&philos);
	return (EXIT_SUCCESS);
}
