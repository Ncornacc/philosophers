/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 13:47:13 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/07/19 13:46:54 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// This is going to be the function repeated over and over by the philos, it's gonna also start a 
//	"Thread control" function to verify that every phiols reached death or reached the right ammount of time
void	*thread_routine(void *philosopher_p)
{
	t_philo	*philos;

	philos = (t_philo *) philosopher_p;
	philos->time_to_die = philos->data->death_time + get_millisec();
	if (pthread_create(&philos->thread_1, NULL, &thread_control, (void *)philos) != 0)
		return ((void *)1);
	while (philos->data->dead == 0)
	{
		eat_action(philos);
		write_action("Is Thinking", philos);
	}
	if (pthread_join(philos->thread_1, NULL) != 0)
		return ((void *)1);
	return ((void *)0);
}

void *thread_control(void *philosopher_p)
{
	t_philo *philos;

	philos = (t_philo *) philosopher_p;
	while (philos->data->dead == 0)
	{
		pthread_mutex_lock(&philos->lock);
		if (get_millisec() >= philos->time_to_die && philos->is_eating == 0)
			write_action("Died", philos);
		if (philos->eat_counter == philos->data->number_of_meals)
		{
			pthread_mutex_lock(&philos->data->lock);
			philos->data->finished++;
			philos->eat_counter++;
			pthread_mutex_unlock(&philos->data->lock);
		}
		pthread_mutex_unlock(&philos->lock);
	}
	return ((void *) 0);
}

/* 	This function starts if we have the optional parameter. It checks if the status 
	of all the philos is marked as "finished", and in that case it stops the threads. */
void *thread_check(void *info_pointer)
{
	t_philo	*philos;

	philos = (t_philo *) info_pointer;
	pthread_mutex_lock(&philos->data->unlock);
	printf(BLUE"Data Value %d", philos->data->dead);
	pthread_mutex_unlock(&philos->data->unlock);
	while (philos->data->dead == 0)
	{
		pthread_mutex_lock(&philos->lock);
		if (philos->data->finished >= philos->data->number_of_philo)
			philos->data->dead = 1;
		pthread_mutex_unlock(&philos->lock);
	}
	return ((void *) 0);
} 

int	start_threads(t_info *info)
{
	int			index;
	pthread_t	thread_0;

	index = -1;
	info->start_time = get_millisec();
	if (info->number_of_meals > 0)
	{
		if (pthread_create(&thread_0, NULL, &thread_check, &info->philosopher[0]))
			return (error_msg("Error Creating the thread", info));
	}
	while (++index < info->number_of_philo)
	{
		if (pthread_create(&info->thread_id[index], NULL, &thread_routine, &info->philosopher[index]))
			return (error_msg(RED"problem creating the Thread", info));
		ft_usleep(1);
	}
	index = -1;
	while (++index < info->number_of_philo)
	{
		if (pthread_join(info->thread_id[index], NULL))
			return (error_msg(YELLOW"ERROR with Joining the Threads", info));
	}
	return (0);
}