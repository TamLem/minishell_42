/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:43:40 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/02 11:43:13 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 

[simple command] = [executable [argument]*]

[input redirection] = [<filename]

[output redirection] = [>filename]

[append redirection] = [>>filename]

[heredoc] = [<<delimiter]

[redirection] = [[input redirection] / [output redirection] / [append redirection] / [heredoc]]

[command] = [[simple command] [redirection]*]

[pipeline] = [[command]] [ | [command]]*]


[redirection] [io_file] [cmd] [args..]

[cmd] [redirection] [io_file] [args..]

[cmd] [args..] [redirection] [io_file]

 */

// void ft_perror(int	err_code, char *msg)
// {
// 	printf("error:\n%s", msg);
// 	mem_free();
// 	if (err_code_need_exit)
// 		exit(0);
// }

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

int	lex_err(void)
{
	
	return (0);
}

int	is_io_redir(t_token *token)
{
	int	type;

	type = token->type;
	if (type == LESS || type == DLESS || type == GREAT || type == DGREAT)
		return (true);
	return (false);
}

int	check_syntax(void)
{
	int		args;
	t_token	*token;

	args = 0;
	token = g_data.tokens;
	while (token)
	{
		if (is_io_redir(token) && token->next && is_io_redir(token->next))
		{
			token->error = true;
			return (err_handle(4, token->value));
		}
		if ((is_io_redir(token) && token->type != DLESS)
			&& (!token->next && token->type != REDIR))
		{
			token->error = true;
			return (err_handle(5, token->value));
		}
		token->error = false;
		token = token->next;
		// if (arg == 0 && token->type != REDIR && token->type != WORD)
		// 	return (error_handle())
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
	err[6] = "No such file or directory";
	if (error_code == 0)
		print_err("minishell: %s: %s\n", error_input, err[0]);
	if (error_code == 1)
		print_err("minishell: %s: %s\n", error_input, err[1]);
	if (error_code == 2)
		print_err("minishell: %s: %s\n", error_input, err[2]);
	if (error_code == 3)
		print_err("minishell: %s: %s\n", error_input, err[3]);
	if (error_code == 4)
		print_err("minishell: %s: `%s'\n", err[4], error_input);
	if (error_code == 5)
		print_err("minishell:%s %s\n", "", err[5]);
	if (error_code == 6)
		print_err("minishell:%s %s\n", "", err[6]);
	g_data.exit_status = error_code;
	return (error_code);
}
