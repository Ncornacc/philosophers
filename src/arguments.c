/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arguments.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ncornacc <ncornacc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/19 11:02:25 by ncornacc      #+#    #+#                 */
/*   Updated: 2023/07/19 11:38:24 by ncornacc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check(int num)
{
	if (num >= 48 && num <= 57)
		return (TRUE);
	else
		return (FALSE);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[++i])
	{
		if (check(str[i]) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

int	arguments_content(char **argv)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (is_numeric(argv[i]))
			continue ;
		else
			return (FALSE);
	}
	return (TRUE);
}

int	arguments_number(int argc)
{
	if (argc < 5 || argc > 6)
		return (FALSE);
	else
		return (TRUE);
}

int	check_arguments(int argc, char **argv)
{
	if (arguments_number(argc) && arguments_content(argv))
	{
		if (limits(argv))
			return (TRUE);
		return (print_error(), FALSE);
	}
	return (print_syntax(), FALSE);
}