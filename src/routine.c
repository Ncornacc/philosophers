/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   routine.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 10:15:52 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/09/20 10:49:26 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void    *philos_routine(void *args)
{
    t_info  *info;
    int     index;

    info = (t_info *)args;
    index = info->number_of_threads;
    if (info->args.num_time_to_eat > 0)
    {
        while (info->args.num_time_to_eat > info->philo[index].eat_time_counter
            && info->is_philo_dead == FALSE)
            execute_routine(info, index);
    }
    else
    {
        while (info->is_philo_dead == FALSE)
        {
            if (execute_routine(info, index) == FALSE)
                break ;
        }
    }
    return (NULL);
}

int execute_routine(t_info *info, int index)
{
    if (eating(info, index) == FALSE)
        return (FALSE);
    if (info->args.num_time_to_eat != info->philo[index].eat_time_counter)
    {
        if (sleeping(info, index) == FALSE)
            return (FALSE);
        if (thinking(info, index) == FALSE)
            return (FALSE);
    }
    return (TRUE);
}

void    *philos_monitor(void *args)
{
    t_info  *info;
    int     index;

    info = (t_info *)args;
    index = 0;
    if (info->args.num_time_to_eat > 0)
    {
        while (info->args.num_time_to_eat > info->philo[index].eat_time_counter
            && info->is_philo_dead == FALSE)
        {
            if (philos_dead(info, &index) == TRUE)
                break ;
        }
    }
    else
    {
        while (info->is_philo_dead == FALSE)
        {
            if (philos_dead(info, &index) == TRUE)
                break ;
        }
    }
    return (NULL);
}

int print_philo(t_info *info, int id, char *color, char *message)
{
    long long   current_time;

    current_time = get_delta(info->time);
    if (info->is_philo_dead == TRUE)
        return (FALSE);
    pthread_mutex_lock(&info->print);
    if (info->is_philo_dead == TRUE)
    {
       pthread_mutex_unlock(&info->print);
       return (FALSE); 
    }
    else
        printf("%s%-10lld %-3d %-30s%s\n", color, current_time, id, 
            message, DEF_COLOR);
    pthread_mutex_unlock(&info->print);
    return (TRUE);
}

void    free_philo(t_info *info)
{
    free(info->philo);
    free(info->forks);
}


