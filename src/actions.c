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

void    eat_action(t_philo *philos)
{
	take_forks(philos);
	pthread_mutex_lock(&philos->lock);
	philos->is_eating = 1;
	philos->time_to_die = get_millisec() + philos->data->death_time;
	write_action("is eating", philos);
	philos->eat_counter++;
	ft_usleep(philos->data->eat_time);
	philos->is_eating = 0;
	pthread_mutex_unlock(&philos->lock);
	leave_forks(philos);
}

void	write_action(char *str, t_philo *philos)
{
	u_int64_t	time;

	pthread_mutex_lock(&philos->data->unlock);
	time = get_millisec() - philos->data->start_time;
	if (ft_strcmp("Died", str) == 0 && philos->data->dead == 0)
	{
		printf("%llu %d %s\n", time, philos->id, str);
		philos->data->dead = 1;
	}
	if (!philos->data->dead)
		printf("%llu %d %s\n", time, philos->id, str);
	pthread_mutex_unlock(&philos->data->unlock);
}

void	take_forks(t_philo *philos)
{
	pthread_mutex_lock(philos->right_fork);
	write_action("has taken a fork", philos);
	pthread_mutex_lock(philos->left_fork);
	write_action("has taken a fork", philos);
}

void	leave_forks(t_philo *philos)
{
	pthread_mutex_unlock(philos->left_fork);
	pthread_mutex_unlock(philos->right_fork);
	write_action("is sleeping", philos);
	ft_usleep(philos->data->sleep_time);
}

