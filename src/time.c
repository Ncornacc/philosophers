/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncornacc <ncornacc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:14:01 by ncornacc          #+#    #+#             */
/*   Updated: 2023/09/20 09:42:10 by ncornacc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// we do tv_sec * 1000 cause 1 second = 1000 milliseconds
// we do tv_usec * 0.001 cause 1 microsecond = 0.001 milliseconds

long long	get_delta(long long time)
{
	if (time > 0)
		return (get_time() - time);
	return (FALSE);
}

void	execute_action(long long time)
{
	usleep(time * 1000);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_usec * 0.001) + (time.tv_sec * 1000));
}