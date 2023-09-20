/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   actions.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 10:50:11 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/09/20 11:15:12 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int eating(t_info *info, int index)
{
    if (pthread_mutex_lock(&info->forks[info->philo[index].fork.left]) != 0)
        return (FALSE);
    if (print_philo(info, info->philo[index].id, GREEN, TAKE_FORKS) == FALSE)
        return (FALSE);
    if (pthread_mutex_lock(&info->forks[info->philo[index].fork.right]) != 0)
        return (FALSE);
    if (print_philo(info, info->philo[index].id, GREEN, TAKE_FORKS) == FALSE)
        return (FALSE);
    if (print_philo(info, info->philo[index].id, YELLOW, EATING) == FALSE)
        return (FALSE);
    info->philo[index].time_to_die = get_time();
    execute_action(info->args.time_to_eat);
    leave_forks(info, index);
    return (TRUE);
}

int leave_forks(t_info *info, int index)
{
    if (pthread_mutex_unlock(&info->forks[info->philo[index].fork.left]))
        return (FALSE);
    if (pthread_mutex_unlock(&info->forks[info->philo[index].fork.right]))
        return (FALSE);
    info->philo[index].eat_time_counter++;
    return (TRUE);
}

int sleeping(t_info *info, int index)
{
    if (print_philo(info, info->philo[index].id, BLUE, SLEEPING) == FALSE)
        return (FALSE);
    execute_action(info->args.time_to_sleep);
    return (TRUE);
}

int thinking(t_info *info, int index)
{
    if (print_philo(info, info->philo[index].id, MAGENTA, THINKING) == FALSE)
        return (FALSE);
    return (TRUE);
}

int philos_dead(t_info *info, int *index)
{
    int time;

    if (*index == info->args.number_of_philo)
        *index = 0;
    time = get_delta(info->philo[*index].time_to_die);
    if (time > info->args.time_to_die)
    {
        print_philo(info, info->philo[*index].id, PINK, DIED);
        info->is_philo_dead = TRUE;
        return (TRUE);
    }
    index++;
    return (FALSE);
}