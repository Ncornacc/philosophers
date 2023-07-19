/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/17 12:15:06 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/07/19 11:39:55 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// function that reports an Error by printing and calls a function that clears all the memory allocations and mutexes
int	error_msg(char *str, t_info *info)
{
	printf("%s\n", str);
	if (info)
		end_routine(info);
	return (1);
}

// Funcion to get the current millisecond
u_int64_t	get_millisec(void)
{
	struct timeval	tv;
	
	if (gettimeofday(&tv, NULL))
		return (error_msg("gettimeofday() FAILURE\n", NULL));
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

// Simple recreation of the usleep function
int	ft_usleep(useconds_t time)
{
	u_int64_t	start;
	start = get_millisec();
	while ((get_millisec() - start) < time)
		usleep(time / 10);
	return(0);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(char *)s1 - *(char *)s2);
}

int	ft_atoi(const char *nptr)
{
	int	final_num;
	int	i;
	int	sign;

	final_num = 0;
	i = 0;
	sign = 1;
	while (nptr[i] == '\f' || nptr[i] == '\n' || nptr[i] == '\r'
		|| nptr[i] == '\t' || nptr[i] == '\v' || nptr[i] == ' ')
		i++;
	if (nptr[i] && nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	if (nptr[i] >= '0' && nptr[i] <= '9')
	{
		while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
			final_num = (final_num * 10) + (nptr[i++] - '0');
	}
	else
		return (0);
	return (final_num * sign);
}
