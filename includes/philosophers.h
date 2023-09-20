/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 11:21:46 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/09/20 11:15:45 by ncornacc      ########   odam.nl         */
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
# define PINK "\e[0;38;5;199m"
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
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>/* For pthread Functions */
# include <sys/time.h>/* gettimeofday */
# include <limits.h>

/* STRUCT */

typedef struct s_forks
{
	int	left;
	int	right;
}	t_forks;

typedef struct s_arguments
{
	int	number_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_time_to_eat;
}	t_args;

typedef struct s_philosopher
{
	int			eat_time_counter;
	int			id;
	long long	time_to_die;
	pthread_t	thread;
	t_forks		fork;
}	t_philo;

typedef struct s_informations
{
	int				number_of_threads;
	int				is_philo_dead;
	long long		time;
	t_philo			*philo;
	t_args			args;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;		
}	t_info;


/*------------FUNCTIONS---------- */

//ARGUMENT CHECK FUNCTIONS
int	initialize_struct(int argc, char **argv, t_info *info);
int	check_arguments(int argc, char **argv, t_info *info);


// PHILOSOPHER FUNCTIONS
void	initialize_philos_struct(t_info *info, int index, int counter);
int		philosophers_born(t_info *info);
int		one_philo(t_info *info);
void    *philos_routine(void *args);
int		execute_routine(t_info *info, int index);
void    *philos_monitor(void *args);
void	forks_unlock(t_info *info);
int		forks_born(t_info *info);
int		print_philo(t_info *info, int id, char *color, char *message);

// UTILS FUNCTION
int			ft_atoi(char *str);
long long	get_delta(long long time);
void		execute_action(long long time);
long long	get_time(void);
void   		free_philo(t_info *info);

// THREAD FUNCTIONS
int threads_born(t_info *info);
int threads_dead(t_info *info);
int threads_join(t_info *info);

// ACTION FUNCTIONS
int sleeping(t_info *info, int index);
int leave_forks(t_info *info, int index);
int eating(t_info *info, int index);
int thinking(t_info *info, int index);
int philos_dead(t_info *info, int *index);



#endif