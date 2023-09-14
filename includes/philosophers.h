/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 11:21:46 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/07/19 11:40:17 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* DEFINED USER COLOR*/
# define DEF_COLOR "\033[0;39m"
# define GRAY "\033[0;90m"
# define RED "\033[0;91m"
# define GREEN "\033[0;92m"
# define YELLOW "\033[0;93m"
# define BLUE "\033[0;94m"
# define MAGENTA "\033[0;95m"
# define CYAN "\033[0;96m"

/* DEFINED USER MESSAGES */
# define TRUE 		1
# define ERROR		0
# define FALSE		0
# define DIED 		"died"
# define EATING 	"is eating"
# define THINKING 	"is thinking"
# define SLEEPING 	"is sleeping"
# define TAKE_FORKS	"has taken a fork"

/* INCLUDES LIBRARIES */
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>/* For pthread Functions */
# include <sys/time.h>/* gettimeofday */
# include <limits.h>

/* STRUCT */

typedef struct s_philosophers
{
	struct s_info		*data;
	pthread_t			thread_id;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	int					id;
	int					last_eat;
	int					eat_counter;
	int					is_eating;
}	t_philo;

typedef struct s_info
{
	int					number_of_philo;
	int					time_to_die;
	int					time_to_sleep;
	int					time_to_eat;
	int					number_of_meals;
	int					dead;
	int					start_time;
	t_philo				*philosopher;
	pthread_mutex_t		*fork_mutex;
	pthread_mutex_t		lock;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
}	t_info;


/*------------FUNCTIONS---------- */

// INIT FUNC
int		create_struct(t_info *info, char **argv);
int		init_philos(t_info *info);
int		create_mutex(t_info *info);

// Arguments Func
int		arguments_number(int argc);
int		arguments_content(char **argv);
int		check_arguments(int argc, char **argv);
int		is_numeric(char *str);
int		check(int num);
int		limits_check(char *str);
int		limits(char **argv);
void	print_syntax(void);
void	print_error(void);

// UTILS
int		ft_atoi(const char *str);
long	ft_atoi_long(const char *str);
int		get_time(void);
void	ft_sleep(int numb, t_philo *philo);
void	print_msg(char *str, t_philo *philo);

//Actions Func
void	start_routine(t_info *info);
void	*philos_routine(void *args);
void	*start_monitor(void *args);
void	thread_join(t_info *info);
void	free_philo(t_info *info);
int		philos_dead(t_philo *philo);
void	philos_eating(t_philo *philos);
void	philos_sleeping(t_philo *philos);
void	philos_thinking(t_philo *philos);
int		philos_forks(t_philo *philo);
int		is_dead(t_info *info);
int		has_eaten(t_philo *philo);

#endif