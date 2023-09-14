/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arguments_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 11:02:25 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/07/19 11:38:24 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	limits_check(char *str)
{
	if (ft_atoi_long(str) > INT_MAX || ft_atoi_long(str) < INT_MIN)
		return (TRUE);
	return (FALSE);
}

int	limits(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (limits_check(argv[i]))
			return (FALSE);
	}
	return (TRUE);
}

void	print_error(void)
{
	printf("\nNo arguments - should be above the int limits!\n\n");
}

void	print_syntax(void)
{
	printf("\n./philo[philos][death_time][eating_time][sleeping_time]\n\n");
}
