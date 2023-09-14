/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 11:02:25 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/07/19 11:38:24 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	free_philo(t_info *info)
{
	free(info->philosopher);
	free(info->fork_mutex);
}

void	*start_monitor(void *args)
{
	t_info	*info;

	info = (t_info *)args;
	while (1)
	{
		pthread_mutex_lock(&info->lock);
		if (is_dead(info) == 0)
		{
			usleep(100);
			return (pthread_mutex_unlock(&info->lock), NULL);
		}
		pthread_mutex_unlock(&info->lock);
	}
}

void	*philos_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (philo->data->dead == 0)
	{
		if (philos_dead(philo))
			return (0);
		philos_forks(philo);
		if (philos_dead(philo))
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		philos_eating(philo);
		if (philos_dead(philo))
			return (0);
		philos_sleeping(philo);
		if (philos_dead(philo))
			return (0);
		philos_thinking(philo);
	}
	return (0);
}

void	start_routine(t_info *info)
{
	int	i;

	i = 0;
	info->start_time = get_time();
	while (i < info->number_of_philo)
	{
		pthread_create(&info->philosopher[i].thread_id, NULL, 
			&philos_routine, (void *)&info->philosopher[i]);
		i++;
	}
	i = 0;
	while (i < info->number_of_philo)
	{
		pthread_join(info->philosopher[i].thread_id, NULL);
		i++;
	}
}