/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 10:00:47 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/09/20 10:16:15 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int threads_born(t_info *info)
{
    int index;

    index = 0;
    info->is_philo_dead = FALSE;
    info->time = get_time();
    if (pthread_mutex_init(&info->print, NULL) != 0)
        return (FALSE);
    while (index < info->args.number_of_philo)
    {
        info->number_of_threads = index;
        if (pthread_create(&info->philo[index].thread, NULL, &philos_routine, 
            (void *) info) != 0)
            return (FALSE);
        index++;
        usleep(1000);
    }
    if (pthread_create(&info->monitor, NULL, &philos_monitor, (void *) info)
        != 0)
        return (FALSE);
    usleep(1000);
    if (threads_join(info) == FALSE)
        return (FALSE);
    return (TRUE);
}

int threads_join(t_info *info)
{
    int index;

    index = 0;
    while (index < info->args.number_of_philo)
    {
        if (pthread_join(info->philo[index].thread, NULL) != 0)
            return (FALSE);
        index++;
    }
    if (pthread_join(info->monitor, NULL) != 0)
        return (FALSE);
    return (TRUE);
}

int threads_dead(t_info *info)
{
    int index;

    index = 0;
    while (index < info->args.number_of_philo)
    {
        pthread_mutex_destroy(&info->forks[index]);
        index++;
    }
    pthread_mutex_destroy(&info->print);
    return (TRUE);
}