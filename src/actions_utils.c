/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 11:02:25 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/07/19 11:38:24 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philos_thinking(t_philo *philos)
{
	print_msg("is thinking", philos);
}

void	philos_sleeping(t_philo *philos)
{
	print_msg("is sleeping", philos);
	ft_sleep(philos->data->time_to_sleep, philos);
}

void	philos_eating(t_philo *philo)
{
	print_msg("is eating", philo);
	pthread_mutex_lock(&philo->data->lock);
	philo->last_eat = get_time() - philo->data->start_time;
	philo->time_to_die = philo->last_eat + philo->data->time_to_die;
	pthread_mutex_unlock(&philo->data->lock);
	ft_sleep(philo->data->time_to_eat, philo);
	pthread_mutex_lock(&philo->data->lock);
	if (philo->eat_counter != -1)
		philo->eat_counter++;
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	philos_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
}

int	philos_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	if (!philos_dead(philo))
		print_msg("has taken a fork", philo);
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(philo->left_fork) != 0)
			return (pthread_mutex_unlock(philo->right_fork), 1);
		if (!philos_dead(philo))
			print_msg("has taken a fork", philo);
	}
	else
	{
		if (pthread_mutex_lock(philo->right_fork) != 0)
			return (pthread_mutex_unlock(philo->left_fork), 1);
		if (!philos_dead(philo))
			print_msg("has taken a fork", philo);
	}
	return (0);
}