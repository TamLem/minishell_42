/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:22:51 by nlenoch           #+#    #+#             */
/*   Updated: 2022/04/03 16:23:43 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "xecutor.h"

bool	check_flag(char *arg, char *flag)
{
	bool	is_flag;
	int		flaglen;

	flaglen = ft_strlen(flag);
	is_flag = false;
	if (ft_strncmp(arg, flag, flaglen) == 0)
	{
		is_flag = true;
		while (arg[flaglen])
		{
			if (arg[flaglen] != flag[1])
				is_flag = false;
			flaglen++;
		}
	}
	return (is_flag);
}

void	echo_print(bool n_flag, char **argv)
{
	while (*argv)
	{
		printf("%s", *argv);
		argv++;
		if (*argv)
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
}

void	ft_printhelp(bool n_flag, char **argv)
{
	int	i;

	i = 1;
	if (n_flag)
		i = 2;
	while (argv[i] && (i == n_flag + 1 || printf(" ")))
	{
		printf("%s", argv[i]);
		i++;
	}
	if (!n_flag)
		printf("\n");
}

int	ft_echo(int argc, char **argv)
{
	int		i;
	bool	n_flag;

	i = 1;
	n_flag = false;
	if (argc == 1)
	{
		printf("\n");
		return (0);
	}
	while (argv[i] && check_flag(argv[i], "-n"))
		i++;
	if (i > 1)
		n_flag = true;
	echo_print(n_flag, &(argv[i]));
	return (0);
}
