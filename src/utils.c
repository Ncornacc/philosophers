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

int	ft_atoi(const char *nptr)
{
	int	final_num;
	int	i;
	int	sign;

	final_num = 0;
	i = 0;
	sign = 1;
	while (nptr[i])
	{
		while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
			i++;
		if (nptr[i] == '+' || nptr[i] == '-')
		{
			if (nptr[i] == '-')
				sign = -1;
			i++;
		}
		while (nptr[i] >= '0' && nptr[i] <= '9')
		{
			final_num = (final_num * 10) + nptr[i] - 48;
			i++;
		}
		return (final_num * sign);
	}
	return (0);
}

long	ft_atoi_long(const char *str)
{
	long	final_long;
	long	sign;
	int		i;

	final_long = 0;
	sign = 1;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		if (str[i] == '+' || str[i] == '-')
		{
			if (str[i] == '-')
				sign = -1;
			i++;
		}
		while (str[i] >= '0' && str[i] <= '9')
		{
			final_long = (final_long * 10) + str[i] - 48;
			i++;
		}
		return (final_long * sign);
	}
	return (0);
}

void	print_msg(char *str, t_philo *philo)
{
	if (!philos_dead(philo))
	{
		pthread_mutex_lock(&philo->data->lock);
		printf("%d %d %s\n", get_time() - philo->data->start_time, 
			philo->id, str);
		pthread_mutex_unlock(&philo->data->lock);
	}
}

int	get_time(void)
{
	static struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_sleep(int numb, t_philo *philo)
{
	int	time;

	time = get_time();
	while ((get_time() - numb) < time && philos_dead(philo) == FALSE)
		usleep(50);
}
