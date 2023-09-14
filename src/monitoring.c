/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 11:02:25 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/07/19 11:38:24 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	thread_join(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philo)
	{
		pthread_join(info->philosopher[i].thread_id, NULL);
		i++;
	}
}

int	has_eaten(t_philo *philo)
{
	if (get_time() - philo->data->start_time > philo->time_to_die)
	{
		philo->data->dead = 1;
		printf("%d %d died\n", get_time() - philo->data->start_time, philo->id);
		return (0);
	}
	else
		return (1);
}

int	is_dead(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->number_of_philo)
	{
		if (has_eaten(&info->philosopher[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}