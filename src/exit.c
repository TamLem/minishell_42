/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:33:19 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/28 18:41:26 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* exits bash through either sending a signal or killing processes */
#include "minishell.h"
#include "xecutor.h"

int	ft_exit(int argc, char **argv)
{
	exit(0);
	return (0);
}
