/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:33:19 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/26 17:32:53 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* exits bash through either sending a signal or killing processes */
#include "minishell.h"
#include "xecutor.h"

int ft_exit(int argc, char **argv)
{
	exit(0);
	return (0);
}
