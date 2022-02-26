/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:22:51 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/26 19:24:57 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// string can be in "qotes" or without
// if string includes '$PWD' return print current working directory with rest of string
// if option '-n' do not print a newline

#include "minishell.h"
#include "xecutor.h"

static bool	check_flag(char *arg, char *flag)
{
	if (ft_strncmp(arg, flag, ft_strlen(flag)) != 0)
		return (false);
	arg = arg + ft_strlen(flag);
	while (*arg)
	{
		if (*arg != *(flag + 1))
			return (false);
		arg++;
	}
	return (true);
}
int	ft_echo(int argc, char **argv)
{
	int		i;
	bool	flag_n;

	if (argc == 1)
	{
		printf("\n");
		return (0);
	}
	i = 1;
	flag_n = check_flag(argv[1], "-n");
	if (flag_n)
		i = 2;
	while (argv[i] && (i == 1 || printf(" ")))
	{
		printf("%s", argv[i]);
		i++;
	}
	if (!flag_n)
		printf("\n");
	return (0);
}