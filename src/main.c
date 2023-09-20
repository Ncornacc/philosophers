/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncornacc <ncornacc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:31:01 by ncornacc          #+#    #+#             */
/*   Updated: 2023/09/19 16:09:19 by ncornacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_info	info;

	if (!check_arguments(argc, argv, &info))
		return (TRUE);
	if (!philosophers_born(&info))
		return (TRUE);
	if (!forks_born(&info))
		return (TRUE);
	if (info->args->number_of_philo == 1)
	{
		if (!one_philo(&info))
			return (TRUE);
		return (FALSE);
	}
	return (FALSE);
}
