/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialization.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 12:39:27 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/07/19 11:36:29 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int struct_init(t_info *info, char **argv, int argc)
{
    info->number_of_philo = (int)ft_atoi(argv[1]);
    info->death_time = (u_int64_t)ft_atoi(argv[2]);
    info->eat_time = (u_int64_t)ft_atoi(argv[3]);
    info->sleep_time = (u_int64_t)ft_atoi(argv[4]);
    if (argc == 5)
        info->number_of_meals = -1;
    else
        info->number_of_meals = (int)ft_atoi(argv[5]);
    // Here we check that everything went correctly
    if (info->death_time < 0 || info->eat_time < 0 || info->sleep_time < 0
        || info->number_of_philo <= 0)
        return(error_msg(RED"Problem with data into info struct", NULL));
    info->finished = 0;
    info->dead = 0;
    pthread_mutex_init(&info->lock, NULL);
    pthread_mutex_init(&info->unlock, NULL);
    return (0);
}

int pointer_alloc(t_info *info)
{
    info->thread_id = malloc(sizeof(pthread_t) * info->number_of_philo);
    if (!info->thread_id)
        return(error_msg(RED"Problem with thread id allocation", info));
    info->philosopher = malloc(sizeof(t_philo) * info->number_of_philo);
    if (!info->philosopher)
        return(error_msg(RED"Problem with philo allocation", info));
    info->forks = malloc(sizeof(pthread_mutex_t) * info->number_of_philo);
    if (!info->forks)
        return(error_msg(RED"Problem with forks allocation", info));
    return(0);
}

int forks_init(t_info *info)
{
    int index;

    index = -1;
    while(++index < info->number_of_philo)
        pthread_mutex_init(&info->forks[index], NULL);
    index = 0;
    info->philosopher[0].left_fork = &info->forks[0];
    info->philosopher[0].right_fork = &info->forks[info->number_of_philo - 1];
    index++;
    while (index < info->number_of_philo)
    {
        info->philosopher[index].left_fork = &info->forks[index];
        info->philosopher[index].right_fork = &info->forks[index - 1];
        index++;
    }
    return (0);
}

void philosophers_init(t_info *info)
{
    int index;

    index = -1;
    while (++index < info->number_of_philo)
    {
        info->philosopher[index].data = info;
        info->philosopher[index].eat_counter = 0;
        info->philosopher[index].id = index + 1;
        info->philosopher[index].time_to_die = info->death_time;
        info->philosopher[index].is_eating = 0;
        info->philosopher[index].status = 0;
        pthread_mutex_init(&info->philosopher[index].lock, NULL);
    }
    
}

//we need to initialize singularly the struct with the user input, allocate the pointers in the struct and init the mutexes

int program_init(t_info *info, char **argv, int argc)
{
    if (struct_init(info, argv, argc) != 0)
        error_msg(RED"Problem initalazing the struct", NULL);
    if (pointer_alloc(info) != 0)
        error_msg(RED"Problem with pointer allocations (tid, forks, philo)", NULL);
    if (forks_init(info) != 0)
        error_msg(RED"Problem with mutex forks creation", NULL);
    philosophers_init(info);
    return (0);
}