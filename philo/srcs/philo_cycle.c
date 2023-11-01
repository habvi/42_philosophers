#include "philo.h"

// todo: error
static t_result	wait_start_cycle(t_args *args)
{
	if (pthread_mutex_lock(&args->start_cycle) != MUTEX_SUCCESS)
		return (FAILURE);
	if (pthread_mutex_unlock(&args->start_cycle) != MUTEX_SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

// todo: error
bool	is_any_philo_died(const t_philo *philo)
{
	pthread_mutex_t	*for_death;
	bool			is_any_philo_died;

	for_death = &philo->args->for_death;
	if (pthread_mutex_lock(for_death) != MUTEX_SUCCESS)
		return (false); // todo: FAILURE
	is_any_philo_died = philo->args->is_any_philo_died;
	if (pthread_mutex_unlock(for_death) != MUTEX_SUCCESS)
		return (false); // todo: FAILURE
	return (is_any_philo_died);
}

static t_result	philo_action(\
					const t_philo *philo, t_result (*action)(const t_philo *))
{
	if (is_any_philo_died(philo))
		return (SUCCESS);
	action(philo);
	return (SUCCESS);
}

// todo: return t_result?
void	*philo_cycle(void *thread_args)
{
	const t_philo	*philo = (const t_philo *)thread_args;

	if (wait_start_cycle(philo->args) == FAILURE)
		return (NULL); // todo
	while (!is_any_philo_died(philo))
	{
		// philo_action(philo, &take_two_forks);
		philo_action(philo, &eating);
		// philo_action(philo, &put_two_forks);
		philo_action(philo, &sleeping);
		philo_action(philo, &thinking);
	}
	put_log(philo, MSG_DIED); // todo: erase
	return (NULL);
}
