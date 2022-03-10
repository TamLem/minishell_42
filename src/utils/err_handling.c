/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:43:40 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/10 20:10:26 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_err(char *format, char *s1, char *s2)
{
	int	init_stdout;
	int	res;

	init_stdout = dup(STDOUT_FILENO);
	res = dup2(STDERR_FILENO, STDOUT_FILENO);
	printf(format, s1, s2);
	dup2(STDOUT_FILENO, init_stdout);
	return (0);
}

int	is_redir(t_token *token)
{
	int	type;

	if (token)
	{
		type = token->type;
		if (type == LESS || type == DLESS || type == GREAT || type == DGREAT)
			return (true);
	}
	return (false);
}

int	check_syntax(void)
{
	int		args;
	t_token	*token;
	t_token	*next;

	args = 0;
	token = g_data.tokens;
	while (token)
	{
		next = token->next;
		if ((is_redir(token))
			&& (!next && token->type != REDIR))
		{
			token->error = true;
			return (err_handle(5, token->value));
		}
		else if ((args++ == 0 && is_redir(next) && token->type != WORD)
			|| (is_redir(token) && next && is_redir(next)))
		{
			token->error = true;
			return (err_handle(4, token->value));
		}
		else if (token->type == PIPE && next && next->type == PIPE)
			return (err_handle(6, token->value));
		token = next;
	}
	return (0);
}

int	err_handle(int error_code, char *error_input)
{
	char	*err[7];

	err[0] = "missing ]";
	err[1] = "command not found";
	err[2] = "not an valid identifier";
	err[3] = "no such file or directory";
	err[4] = "syntax error near unexpected token";
	err[5] = "syntax error near unexpected token 'newline'";
	err[6] = "syntax error near unexpected token";
	if (error_code == 0)
		print_err("minishell: %s: %s\n", error_input, err[0]);
	if (error_code == 1)
		print_err("minishell: %s: %s\n", error_input, err[1]);
	if (error_code == 2)
		print_err("minishell: %s: %s\n", error_input, err[2]);
	if (error_code == 3)
		print_err("minishell: %s: %s\n", error_input, err[3]);
	if (error_code == 4 || error_code == 6)
		print_err("minishell: %s: `%s'\n", err[4], error_input);
	if (error_code == 5)
		print_err("minishell:%s %s\n", "", err[5]);
	return (error_code);
}
