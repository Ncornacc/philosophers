/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/19 15:54:11 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/09/20 11:09:21 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	initialize_philos_struct(t_info *info, int index, int counter)
{
	info->philo[index].id = index + 1;
	info->philo[index].eat_time_counter = 0;
	info->philo[index].time_to_die = 0;
	info->philo[index].fork.left = index;
	info->philo[index].fork.right = counter;
}

int	philosophers_born(t_info *info)
{
	int	index;
	int	counter;

	index = 0;
	counter = 1;
	info->philo = malloc(sizeof(t_philo) * (info->args.number_of_philo + 1));
	if (!info->philo)
		return (FALSE);
	while (counter < info->args.number_of_philo)
	{
		initialize_philos_struct(info, index, counter);
		index++;
		counter++;
	}
	counter = 0;
	initialize_philos_struct(info, index, counter);
	return (TRUE);
}

int	forks_born(t_info *info)
{
	int	index;

	index = 0;
	info->forks = malloc(sizeof(pthread_mutex_t) * info->args.number_of_philo
			+ 1);
	if (!info->forks)
		return (FALSE);
	while (index < info->args.number_of_philo)
	{
		if (pthread_mutex_init(&info->forks[index], NULL) != 0)
			return (FALSE);
		index++;
	}
	return (TRUE);
}

void	forks_unlock(t_info *info)
{
	int	index;

	index = 0;
	while (index < info->args.number_of_philo)
	{
		pthread_mutex_unlock(&info->forks[index]);
		index++;
	}
}

int	one_philo(t_info *info)
{
	if (pthread_mutex_init(&info->print, NULL) != 0)
		return (FALSE);
	info->time = get_time();
	print_philo(info, 1, CYAN, TAKE_FORKS);
	execute_action(info->args.time_to_die);
	print_philo(info, 1, PINK, DIED);
	free_philo(info);
	return (TRUE);
}