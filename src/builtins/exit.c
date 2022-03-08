/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:33:19 by nlenoch           #+#    #+#             */
/*   Updated: 2022/03/08 12:24:44 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* exits bash through either sending a signal or killing processes */
#include "minishell.h"
#include "xecutor.h"

int	ft_exit(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc >= 2)
	{
		while (argv[1][i])
		{
			if (!ft_isdigit(argv[1][i]))
			{
				err_handle(1, argv[1]);
				break ;
			}
			i++;
		}
		exit(ft_atoi(argv[1]));
	}
	else
	{
		system("leaks minishell");
		exit(0);
	}
	return (0);
}
