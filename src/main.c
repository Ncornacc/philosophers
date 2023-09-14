/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 11:50:17 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/07/19 11:39:11 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_philos(t_info *info)
{
	int	i;

	i = 0;
	info->philosopher = malloc(sizeof(t_philo) * info->number_of_philo);
	if (!info->philosopher)
		return (FALSE);
	while (i < info->number_of_philo)
	{
		info->philosopher[i].id = i + 1;
		info->philosopher[i].left_fork = &info->fork_mutex[i];
		info->philosopher[i].right_fork = 
			&info->fork_mutex[(i + 1) % info->number_of_philo];
		info->philosopher[i].data = info;
		info->philosopher[i].time_to_die = info->time_to_die;
		info->philosopher[i].time_to_sleep = info->time_to_sleep;
		info->philosopher[i].time_to_eat = info->time_to_eat;
		info->philosopher[i].last_eat = 0;
		info->philosopher[i].is_eating = 0;
		info->philosopher[i].eat_counter = 0;
		i++;
	}
	return (TRUE);
}

int	create_mutex(t_info *info)
{
	int	i;

	i = -1;
	info->fork_mutex = malloc(sizeof(pthread_mutex_t) * info->number_of_philo);
	if (!info->fork_mutex)
		return (FALSE);
	while (++i < info->number_of_philo)
		pthread_mutex_init(&info->fork_mutex[i], NULL);
	pthread_mutex_init(&info->lock, NULL);
	return (TRUE);
}

int	create_struct(t_info *info, char **argv)
{
	info->number_of_philo = ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		info->number_of_meals = ft_atoi(argv[5]);
	else
		info->number_of_meals = -1;
	info->dead = 0;
	if (create_mutex(info) == FALSE)
		return (FALSE);
	if (init_philos(info) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (check_arguments(argc, argv))
	{
		if (create_struct(&info, argv))
		{
			start_routine(&info);
			start_monitor(&info);
			thread_join(&info);
			free_philo(&info);
		}
	}
}