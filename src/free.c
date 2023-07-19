/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 12:37:42 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/07/19 11:35:39 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// A function that frees a part of the memory by destroying the mutexes and 
// Then calling the delete_info funciton that deletes the pointers.

void end_routine(t_info *info)
{
	int index;

	index = -1;
	while(++index < info->number_of_philo)
	{
		// Here we Destroy the mutexes of the struct @param t_philo
		pthread_mutex_destroy(&info->forks[index]);
		pthread_mutex_destroy(&info->philosopher[index].lock);
	}
	pthread_mutex_destroy(&info->unlock);
	pthread_mutex_destroy(&info->lock);
	delete_info(info);
}

void delete_info(t_info *info)
{
	if (info->forks)
		free(info->forks);
	if (info->philosopher)
		free(info->philosopher);
	if (info->thread_id)
		free(info->thread_id);
}