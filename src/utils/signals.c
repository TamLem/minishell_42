/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:36:20 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/09 18:47:14 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <termios.h>

void	bashify_signal(void)
{
	if (g_data.exit_status == 2)
		g_data.exit_status = 130;
	if (g_data.exit_status == 32512)
		g_data.exit_status >>= 8;
}

int	change_ctrlc_sym(bool	value)
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, &attr);
	if (value == true)
	{
		attr.c_lflag |= ECHOCTL;
	}
	if (value == false)
	{
		attr.c_lflag &= ~ECHOCTL;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &attr);
	return (0);
}

void	sig_ctrlc(int sig)
{
	if (g_data.state == HEREDOC)
	{
		printf("\n");
		prompt();
		close(STDIN_FILENO);
	}
	else
	{
		if (g_data.state == EXEC)
			printf("^C");
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	if (g_data.state == IDLE)
		rl_redisplay();
	g_data.state = 0;
}
