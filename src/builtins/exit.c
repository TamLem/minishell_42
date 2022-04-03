/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:33:19 by nlenoch           #+#    #+#             */
/*   Updated: 2022/03/11 16:56:03 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* exits bash through either sending a signal or killing processes */
#include "minishell.h"
#include "xecutor.h"

int	ft_exit(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc > 2)
		err_handle(5, "exit", " too many arguments");
	if (argc >= 2)
	{
		while (argv[1][i])
		{
			if (!ft_isdigit(argv[1][i]))
			{
				err_handle(5, "exit", "numeric argument required");
				exit(255);
			}
			i++;
		}
		exit(ft_atoi(argv[1]));
	}
	else
	{
		exit(g_data.exit_status);
	}
	return (g_data.exit_status);
}
