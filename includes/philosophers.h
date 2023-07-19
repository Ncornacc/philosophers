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
# define DIED "died"
# define EATING "is eating"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"
# define TAKE_FORKS "has taken a fork"

/* INCLUDES LIBRARIES */
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>/* For pthread Functions */
# include<sys/time.h>/* gettimeofday */
# include <stdint.h>/* uint64_t*/

/* STRUCT */

typedef struct s_philosophers
{
	struct s_info		*data;
	pthread_t			thread_1;
	pthread_mutex_t		lock;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	uint64_t			time_to_die;
	int					id;
	int					eat_counter;
	int					status;
	int					is_eating;
}	t_philo;

typedef struct s_info
{
	int				number_of_philo;
	int				number_of_meals;
	int				dead;
	int				finished;
	t_philo			*philosopher;
	pthread_t		*thread_id;
	pthread_mutex_t	lock;
	pthread_mutex_t	unlock;
	pthread_mutex_t	*forks;
	u_int64_t		start_time;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	u_int64_t		death_time;
}	t_info;


/*------------FUNCTIONS---------- */

// UTILS
int	checking_input(char **argv);
int	error_msg(char *str, t_info *info);
int	ft_usleep(useconds_t time);
int	ft_atoi(const char *nptr);
int	ft_strcmp(char *s1, char *s2);
u_int64_t	get_millisec(void);

// FREE
void end_routine(t_info *info);
void delete_info(t_info *info);

// INITIALIZATION
int program_init(t_info *info, char **argv, int argc);
int struct_init(t_info *info, char **argv, int argc);
int pointer_alloc(t_info *info);
int forks_init(t_info *info);
void philosophers_init(t_info *info);

// THREADS
int	start_threads(t_info *info);
void	*thread_check(void *info_pointer);
void	*thread_routine(void *philosopher_p);
void 	*thread_control(void *philosopher_p);

// ACTIONS
void    eat_action(t_philo *philos);
void	write_action(char *str, t_philo *philos);
void	take_forks(t_philo *philos);
void	leave_forks(t_philo *philos);

#endif