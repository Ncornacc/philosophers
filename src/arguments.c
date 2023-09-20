/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncornacc <ncornacc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:33:24 by ncornacc          #+#    #+#             */
/*   Updated: 2023/09/19 15:52:12 by ncornacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_arguments(int argc, char **argv, t_info *info)
{
	if (initialize_struct(argc, argv, info) == FALSE)
	{
		printf(RED"Wrong Number of args\n"DEF_COLOR);
		return (FALSE);
	}
	else if (!info->args.number_of_philo || !info->args.time_to_die
		|| !info->args.time_to_eat || !info->args.time_to_sleep
		|| (argc == 6 && !info->args.num_time_to_eat))
	{
		printf(RED"Wrong Number of args\n"DEF_COLOR);
		return (FALSE);
	}
	return (TRUE);
}

int	initialize_struct(int argc, char **argv, t_info *info)
{
	if (argc == 5 || argc == 6)
	{
		info->args.number_of_philo = ft_atoi(argv[1]);
		info->args.time_to_die = ft_atoi(argv[2]);
		info->args.time_to_eat = ft_atoi(argv[3]);
		info->args.time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			info->args.num_time_to_eat = ft_atoi(argv[5]);
		else
			info->args.num_time_to_eat = -1;
		return (TRUE);
	}
	return (FALSE);
}

int	ft_atoi(char *str)
{
	int			i;
	long int	n;

	i = 0;
	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	if (n < 0 || ((str[i] < '0' || str[i] > '9') && str[i] != '\0')
		|| n > INT_MAX)
		return (0);
	return (n);
}
