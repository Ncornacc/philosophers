/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncornacc <ncornacc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:21:46 by ncornacc          #+#    #+#             */
/*   Updated: 2023/09/19 15:52:20 by ncornacc         ###   ########.fr       */
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
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>/* For pthread Functions */
# include <sys/time.h>/* gettimeofday */
# include <limits.h>

/* STRUCT */

typedef struct s_forks
{
	int	right_fork;
	int	left_fork;
}	t_fork;

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
	t_fork		fork;
	pthread_t	thread;
}	t_philo;

typedef struct s_informations
{
	int				number_of_threads;
	int				is_philo_dead;
	long long		time;
	t_philo			*philo;
	t_arguments		args;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;		
}	t_info;


/*------------FUNCTIONS---------- */

int	initialize_struct(int argc, char **argv, t_info *info);
int	check_arguments(int argc, char **argv, t_info *info);
int	ft_atoi(char *str);

#endif