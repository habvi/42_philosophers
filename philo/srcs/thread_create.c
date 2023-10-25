#include <stdio.h>
#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

static bool	is_within_time_to_die(const t_philo *philo)
{
	const long	start_time = philo->args->start_time;
	const long	current_time = get_current_time();
	const long	elapsed_time = current_time - start_time;

	return (elapsed_time < philo->args->time_to_die);
}

static void	*philo_cycle(void *thread_args)
{
	t_philo	*philo;

	philo = (t_philo *)thread_args;
	// todo: temp
	while (is_within_time_to_die(philo))
	{
		// todo: error(free)
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

// left: smaller number, right: larger number
static void	set_two_forks_for_eash_philo(\
					t_philo *philo, const int i, const t_args *args)
{
	if (i + 1 < args->num_of_philos)
	{
		philo->left_fork = &args->forks[i];
		philo->right_fork = &args->forks[i + 1];
	}
	else
	{
		philo->left_fork = &args->forks[0];
		philo->right_fork = &args->forks[args->num_of_philos - 1];
	}
}

// static void	init_philo_var(t_philo_var *var)
// {
// 	var->start_time_of_cycle = 0;
// }

static t_philo	*set_thread_info(const int i, t_args *args)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * 1);
	if (philo == NULL)
		return (NULL);
	philo->id = i;
	philo->args = args;
	set_two_forks_for_eash_philo(philo, i, args);
	philo->var = (t_philo_var *)malloc(sizeof(t_philo_var) * 1);
	if (philo->var == NULL)
	{
		ft_free((void **)&philo);
		return (NULL);
	}
	// init_philo_var(philo->var);
	return (philo);
}

// todo: exit -> return error
pthread_t	*create_threads(t_args *args)
{
	pthread_t	*threads;
	int			i;
	t_philo		*philo;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * args->num_of_philos);
	if (threads == NULL)
		return (NULL);
	i = 0;
	while (i < args->num_of_philos)
	{
		philo = set_thread_info(i, args);
		if (philo == NULL)
			return (ft_free((void **)&threads));
		if (pthread_create(&threads[i], NULL, philo_cycle, (void *)philo) != THREAD_SUCCESS)
			return (ft_free((void **)&threads));
		args->philos[i] = philo;
		i++;
	}
	return (threads);
}
