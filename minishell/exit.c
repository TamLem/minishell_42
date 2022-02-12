/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:33:19 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/10 22:08:34 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

exits bash through either sending a signal or killing processes

#include <stdlib.h>

int ft_exit(int argc, char **argv)
{
	exit();
	// wait();
	// waitpid();
	// wait3();
	// wait4();
	// kill();
}
