#include <stdio.h>
#include <unistd.h> // usleep
#include "philo.h"
#include "utils.h"

static void	*philo_cycle(void *thread_args)
{
	t_philo	*philo;
	t_args	*args;
	long	start_time;
	long	current_time;

	philo = (t_philo *)thread_args;
	args = philo->args;

	start_time = get_current_time();
	current_time = start_time;
	while ((current_time - start_time) < args->time_to_die)
	{
		// todo: error
		eating(philo, args, start_time, &current_time);
		sleeping(philo, args, start_time, &current_time);
		thinking(philo, start_time, &current_time);
	}
	free(philo);
	return (NULL);
}

static t_philo	*set_thread_info(int i, t_args *args)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * 1);
	// todo: error
	if (philo == NULL)
		return (NULL);
	philo->id = i;
	philo->args = args;
	return (philo);
}

// todo: exit -> return error
pthread_t	*create_threads(t_args *args)
{
	pthread_t	*threads;
	int			i;
	t_philo		*philo;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * args->number_of_philos);
	if (threads == NULL)
		return (NULL);
	i = 0;
	while (i < args->number_of_philos)
	{
		philo = set_thread_info(i, args);
		if (pthread_create(&threads[i], NULL, philo_cycle, philo) != THREAD_SUCCESS)
		{
			perror("pthread_create");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (threads);
}