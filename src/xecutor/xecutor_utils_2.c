/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xecutor_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 12:31:28 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/11 12:17:32 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "xecutor.h"

void	init_fds(int fd[4])
{
	fd[STDIN_INIT] = dup(STDIN_FILENO);
	fd[STDOUT_INIT] = dup(STDOUT_FILENO);
	fd[IN] = dup(fd[STDIN_INIT]);
	fd[OUT] = dup(fd[STDOUT_INIT]);
}

void	reset_fds(int fd[4])
{
	close(fd[IN]);
	close(fd[OUT]);
	dup2(fd[STDIN_INIT], STDIN_FILENO);
	dup2(fd[STDOUT_INIT], STDOUT_FILENO);
	close(fd[STDIN_INIT]);
	close(fd[STDOUT_INIT]);
}
