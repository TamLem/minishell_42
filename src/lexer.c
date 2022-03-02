/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:26:02 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/02 22:25:40 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	save_token(char *line, char *value, int state)
{
	bool	split;
	t_token **token;
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
		if (!is_WSPACE(*line) || state != 0)
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

char	*field_split(char *str)
{
	char	*split;

	split = NULL;
	while (*str)
	{
		if (!is_WSPACE(*str))
		{
			split = ft_append_char(split, *str);
			if (is_WSPACE(*(str + 1)))
				split = ft_append_char(split, WWSPACE);
		}
		str++;
	}
	// free(str);
	return (split);
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

int	paramlen(char *param)
{
	int	len;

	len = 1;
	if (param[len] != '_' && !ft_isalpha(param[len]))
		return (0);
	while (param[len] == '_' || ft_isalnum(param[len]))
		len++;
	return (len);
}

char *expand_single(char *init_token, int var_pos, char *var, bool split)
{
	char	*before;
	char	*before_mid;
	char	*after;
	char	*temp;
	int		len;

	len = paramlen(var + 1);
	var = ft_substr(var, 1, len);
	temp = ft_getenv(var);
	if (temp)
	{
		if (split)
			temp = field_split(temp);
		free(var);
		var = temp;
	}
	else
		return (NULL);
	before = ft_substr(init_token, 0, var_pos);
	after = ft_substr(init_token, var_pos + len + 1, ft_strlen(init_token));
	before_mid = ft_strjoin(before, var);
	// free(before);
	var = ft_strjoin(before_mid, after);
	return (var);
}

int	param_expand(void)
{
	t_token	*token;
	char	*exp_env;
	char	*var;
	int		var_pos;
	int		len;

	token = g_data.tokens;
	while (token)
	{
		var = ft_strchr(token->value, DOLLAR);
		var_pos = ft_strchr_pos(token->value, DOLLAR);
		if (var && *(token->value + 1))
		{
			len = paramlen(var + 1);
			if (*(var + 1) == QMARK)
				exp_env = ft_itoa(g_data.exit_status);
			else if (len != 0)
				exp_env = expand_single(token->value, var_pos, var, token->split);
			// free(token->value);
			token->value = exp_env;
			// free(before_mid);
		}
		else if (token->type == TOKEN && ft_strchr(token->value, PLACE_HOLDER))
			*(ft_strchr(token->value, PLACE_HOLDER)) = DOLLAR;
		if (!ft_strchr(token->value, DOLLAR))
			token = token->next;
	}
	return (0);
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
			if (is_io_redir(token) && token->next && token->next->type == TOKEN)
				token->next->type = REDIR;
		}
		else if (token->type != REDIR)
			token->type = WORD;
		token = token->next;
	}
	return (0);
}

void	del_empty_tokens(void)
{
	t_token	*token;
	t_token	*next_token;

	token = g_data.tokens;
	while (token)
	{
		next_token = token->next;
		if (next_token && next_token->value == NULL)
		{
			token->next = next_token->next;
			free(next_token);
		}
		else
			token = token->next;
	}
}

void	print_tokens()
{
	t_token *temp;

	temp = g_data.tokens;
	while (temp != NULL)
	{
		printf("token\t");
		printf("%d: %s\n", temp->type, temp->value);
		temp = temp->next;
	}
}

int	lex(char *input)
{
	char	*line;
	char	*quoted;

	line = ft_strdup(input);
	g_data.state = 0;	
	while (!quotes_matched(line))
	{
		quoted = readline("> ");
		if (quoted)
			line = ft_strjoin(line, ft_strdup(quoted));
		else
			break ;
	}
	line = ft_strtrim(line, "\n\t ");
	if (!*line)
		return (1);
	tokenize(line);
	param_expand();
	// return(1);
	strip_quotes();
	tokenize_operators();
	del_empty_tokens();
	// print_tokens();
	check_syntax();
	return (0);
}
