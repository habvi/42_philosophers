#include "philo.h"

static int64_t	get_is_error(t_args *args)
{
	return (args->is_error);
}

// todo: is_thread_err?
static bool	wait_start_cycle(t_args *args)
{
	return (call_atomic(&args->shared, get_is_error, args));
}

void	*philo_cycle(void *thread_args)
{
	t_philo	*philo;
	bool	is_error;

	philo = (t_philo *)thread_args;
	is_error = wait_start_cycle(philo->args);
	if (is_error)
		return (NULL);
	while (!is_any_philo_died(philo))
	{
		take_two_forks(philo);
		eating(philo);
		put_two_forks(philo);
		sleeping(philo);
		thinking(philo);
	}
	// put_log(get_elapsed_time(philo), philo->id, MSG_DIED); // todo: erase
	return (NULL);
}
