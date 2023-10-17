#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include "result.h"

# define MUTEX_SUCCESS	0
# define THREAD_SUCCESS	0

// todo: types
typedef struct s_args {
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philo_must_eat;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
}	t_args;

// todo: struct name...
typedef struct s_thread_info {
	int		philo_id;
	t_args	*args;
}	t_thread_info;

/* args */
bool		is_valid_argc(const int argc);
t_args		set_args(const int argc, const char **argv);

/* mutex */
t_result	init_mutex(t_args *args);
void		destroy_mutex(t_args *args);

/* thread_create */
pthread_t	*create_threads(t_args *args);

/* threads */
void		wait_threads(const t_args *args, pthread_t *threads);
void		destroy_threads(pthread_t **threads);

#endif
