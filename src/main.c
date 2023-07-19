/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 11:50:17 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/07/19 11:39:11 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	checking_input(char **argv)
{
	int	index;
	int	counter;

	index = 1;
	while (argv[index])
	{
		counter = 0;
		while (argv[index][counter])
		{
			if (argv[index][counter] == ' ')
			{
				counter++;
				continue ;
			}
			if (argv[index][counter] < 48 || argv[index][counter] > 57)
				return (error_msg(RED"Error with Input, try again!", NULL));
			counter++;
		}
		index++;
	}
	return (0);
}

int	single_philo(t_info *info)
{
	info->start_time = get_millisec();
	if (pthread_create(&info->thread_id[0], NULL, &thread_routine, &info->philosopher[0]) != 0)
		return (error_msg(RED"Problem creating the single thread", info));
	pthread_detach(info->thread_id[0]);
	while (info->dead == 0)
		ft_usleep(1);
	end_routine(info);
	return (0);
}

int main(int argc, char **argv)
{
    t_info	info;

    if (argc < 5 || argc > 6)
        return(error_msg(RED"Problem with n of arguments", NULL));
    if (checking_input(argv) != 0)
        return(error_msg(RED"Problem with content of arguments", NULL));
	if (program_init(&info, argv, argc) != 0)
		return(error_msg(RED"Problem Inserting input into Program data", NULL));
	if (info.number_of_philo == 1)
		return(single_philo(&info));
	if (start_threads(&info) != 0)
		return(error_msg(RED"error with thread creation", NULL));
	end_routine(&info);
	return (0);
}