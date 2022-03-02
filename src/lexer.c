/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:26:02 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/02 02:46:30 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	tokenize(char *line)
{
	t_token	*token;
	int		state;

	g_data.tokens = ft_malloc(sizeof(t_token));
	token = g_data.tokens;
	token->value = NULL;
	g_data.state = 0;
	while (*line != '\0')
	{
		state = get_state(*line);
		if (*line == '$' && state == QUOTE)
			*line = PLACE_HOLDER;
		if (!is_WSPACE(*line) || state != 0)
		{
			token->value = ft_append_char(token->value, *line);
			if (shall_split(line, token->value, state))
			{
				if (is_operator(*line) && state == 0)
					token->type = OPERATOR;
				else
					token->type = TOKEN;
				if (state == DQUOTE)
					token->split = false;
				else
					token->split = true;
				if (*(line + 1) != '\0')
				{
					token->next = ft_malloc(sizeof(t_token));
					if (token->next == NULL)
						return (2);
					token = token->next;
					token->value = NULL;
					token->expanded = false;
				}
			}
		}
		line++;
	}
	token->next = NULL;
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
	//free
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

int	param_expansion(void)
{
	t_token	*token;
	char	*exp_env;

	token = g_data.tokens;
	while (token)
	{
		if ((token->type == TOKEN && *(token->value) == DOLLAR )|| ft_strchr(token->value, '$'))
		{
			if (*(token->value + 1) == QMARK)
				exp_env = ft_itoa(g_data.exit_status);
			else
				exp_env = ft_getenv(token->value + 1);
			if (exp_env == NULL && *(token->value + 1))
					token->value = NULL;
			else 
			{
				if (token->split == true && *(token->value + 1) == QMARK)
					token->value = field_split(exp_env);
				else
					token->value = exp_env;
				token->expanded = true;
				// free(token->value);
			}
		}
		else if (token->type == TOKEN && ft_strchr(token->value, PLACE_HOLDER))
			*(ft_strchr(token->value, PLACE_HOLDER)) = DOLLAR;
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
			else if (ft_strcmp(token->value, "||") == 0)
				token->type = ERROR;
			if ((token->type == LESS || token->type == DLESS || token->type
					== GREAT || token->type == DGREAT) && token->next &&
						token->next->type == TOKEN)
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
	param_expansion();
	strip_quotes();
	tokenize_operators();
	del_empty_tokens();
	print_tokens();
	check_syntax();
	return (0);
}
