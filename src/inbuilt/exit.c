/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:33:19 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/25 19:28:18 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* exits bash through either sending a signal or killing processes */
#include "xecutor.h"

int ft_exit(int argc, char **argv)
{
	exit(0);
	return (0);
}
