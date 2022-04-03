/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:26:02 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/11 18:41:13 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	save_token(char *line, char *value, int state)
{
	bool	split;
	t_token	**token;
	int		type;

	if (is_operator(*line) && state == 0)
		type = OPERATOR;
	else
		type = TOKEN;
	if (state == DQUOTE)
		split = false;
	else
		split = true;
	token = &g_data.tokens;
	while (*token != NULL)
		token = &((*token)->next);
	*token = ft_malloc(sizeof(t_token));
	(*token)->value = value;
	(*token)->type = type;
	(*token)->split = split;
	(*token)->error = false;
	(*token)->expanded = false;
	(*token)->next = NULL;
	return (0);
}

int	tokenize(char *line)
{
	int		state;
	char	*token_val;

	token_val = NULL;
	while (*line != '\0')
	{
		state = get_state(*line);
		if (*line == '$' && state == QUOTE)
			*line = PLACE_HOLDER;
		if (!is_wspace(*line) || state != 0)
		{
			token_val = ft_append_char(token_val, *line);
			if (shall_split(line, token_val, state))
			{
				save_token(line, token_val, state);
				token_val = NULL;
			}
		}
		line++;
	}
	return (0);
}

int	strip_quotes(void)
{
	char	*stripped;
	int		state;
	t_token	*token;
	char	*quoted;

	token = g_data.tokens;
	g_data.state = 0;
	while (token)
	{
		stripped = NULL;
		quoted = token->value;
		if (ft_strcmp(quoted, "\"\"") == 0)
			quoted = " ";
		while (quoted && *quoted)
		{
			state = get_state(*quoted);
			if ((*quoted != QUOTE && *quoted != DQUOTE)
				|| (state != *quoted && state != 0))
				stripped = ft_append_char(stripped, *quoted);
			quoted++;
		}
		token->value = stripped;
		token = token->next;
	}
	return (true);
}

int	tokenize_operators(void)
{
	t_token	*token;

	token = g_data.tokens;
	while (token)
	{
		if (token && token->value && token->type == OPERATOR)
		{
			if (ft_strcmp(token->value, "<") == 0)
				token->type = LESS;
			else if (ft_strcmp(token->value, "<<") == 0)
				token->type = DLESS;
			else if (ft_strcmp(token->value, ">") == 0)
				token->type = GREAT;
			else if (ft_strcmp(token->value, ">>") == 0)
				token->type = DGREAT;
			else if (ft_strcmp(token->value, "|") == 0)
				token->type = PIPE;
			if (is_redir(token) && token->next && token->next->type == TOKEN)
				token->next->type = REDIR;
		}
		else if (token->type != REDIR)
			token->type = WORD;
		token = token->next;
	}
	return (0);
}

int	lex(char *input)
{
	char	*line;
	char	*quoted;

	line = ft_strdup(input);
	g_data.state = 0;
	line = ft_strtrim(line, "\n\t ");
	while (!quotes_matched(line))
	{
		quoted = readline("> ");
		if (quoted)
			line = ft_strjoin(line, ft_strdup(quoted));
		else
			break ;
		free(quoted);
	}
	if (!*line)
		return (1);
	tokenize(line);
	param_expand();
	strip_quotes();
	tokenize_operators();
	del_empty_tokens();
	return (check_syntax());
}
