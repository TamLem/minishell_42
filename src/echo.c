/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:22:51 by nlenoch           #+#    #+#             */
/*   Updated: 2022/03/02 11:15:16 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "xecutor.h"

bool	check_flag(char *arg, char *flag)
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
	if (argv[1][0] == '-' && argv[1][1] == 'n')
	{
		n_flag = true;
		while (argv[1][i] != '\0' || argv[1][i] == 'n')
		{
			if (argv[1][i] != 'n')
				n_flag = false;
			i++;
		}
	}
	ft_printhelp(n_flag, argv);
	return (0);
}
