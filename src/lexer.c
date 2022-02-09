/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:26:02 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/09 20:01:59 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../include/minishell.h"

int	get_state(char pos);

bool	is_space(char c)
{
	if (c == WSPACE || c == TAB || c == NEWLINE)
		return (true);
	return (false);
}

bool	is_operator(char c)
{
	if (c == LESS || c == GREAT || c == PIPE)
		return (true);
	return (false);
}

bool shall_split(char *line, char *appended, int state)
{
	if (*(line + 1) == '\0')
		return (true);
	if (*(line + 1) == DOLLAR && state != QUOTE)
		return (true);
	if (*appended == DOLLAR && !(ft_isdigit(*(line + 1)) || ft_isalpha(*(line + 1))))
		return (true);
	if (is_space(*(line + 1)) && state == 0)
		return (true);
	if (!is_operator(*line) && is_operator(*(line + 1)))
		return (true);
	if (is_operator(*(line)) && !is_operator(*(line + 1)))
		return (true);
	if (is_operator(*line) && (*line != *appended || ft_strlen(appended) > 1))
		return (true);
	else
		return (false);
}

int	tokenize(char *line)
{
	t_token *token;
	int		state;

	token = &g_data.tokens;
	token->value = NULL;
	g_data.state = 0;
	while(*line != '\0')
	{
		state = get_state(*line);
		if (*line == '$' && state == QUOTE)
			*line = PLACE_HOLDER;
		if (!is_space(*line) || state != 0)
		{
			token->value = ft_append_char(token->value, *line);
			if(shall_split(line, token->value, state))
			{
				if(is_operator(*line))
					token->type = OPERATOR;
				else
					token->type = TOKEN;
				if (state == DQUOTE)
					token->split = false;
				else
					token->split = true;
				if (*(line + 1) != '\0')
				{
					token->next = malloc(sizeof(t_token));
					if (token->next == NULL)
						return (2);
					token = token->next;
					token->value = NULL;
				}
			}
		}
		line++;
	}
	token->next = NULL;
	return (0);
}

int	parse_redir()
{
	t_token	*token;

	token = &g_data.tokens;
	while(token)
	{
		token = token->next;
	}
	return (0);
}

int	get_state(char pos)
{
	int	*state;

	state = &g_data.state;
	if (pos == QUOTE && *state == QUOTE)
		*state = 0;
	else if (pos == QUOTE && *state == 0)
		*state = QUOTE;
	if (pos == DQUOTE && *state == DQUOTE)
		*state = 0;
	else if (pos == DQUOTE && *state == 0)
		*state = DQUOTE;
	return (*state);
}

char	*strip_quotes(char *line)
{
	char	*stripped;
	int		state;

	stripped = NULL;
	g_data.state = 0;
	while(*line)
	{
		state = get_state(*line);
		if (*line == '$' && state != QUOTE)
			stripped = ft_append_char(stripped, '$');
		if (*line == '$' && state == QUOTE)
			stripped = ft_append_char(stripped, PLACE_HOLDER);
		if (*line != '$' && ((*line != QUOTE && *line != DQUOTE) 
			|| (state != *(line) && state != 0)))
			stripped = ft_append_char(stripped, *line);
		line++;
	}
	return (stripped);
}

int	quotes_matched(char *line)
{
	g_data.state = 0;
	while(*line)
	{
		get_state(*line);
		line++;
	}
	if (get_state(*line) == 0)
		return (true);
	else
		return (false);
}

int	tokenize_operators()
{
	t_token *token;

	token = &g_data.tokens;
	while(token)
	{
		if(ft_strcmp(token->value, "<") == 0)
			token->type = LESS;
		else if(ft_strcmp(token->value, "<<") == 0)
			token->type = DLESS;
		else if(ft_strcmp(token->value, ">") == 0)
			token->type = GREAT;
		else if(ft_strcmp(token->value, ">>") == 0)
			token->type = DGREAT;
		else if(ft_strcmp(token->value, "=") == 0)
			token->type = LESS;
		else if(ft_strcmp(token->value, "|") == 0)
			token->type = PIPE;
		else if(ft_strcmp(token->value, "||") == 0)
			token->type = ERROR;
		else if(ft_strchr(token->value, '=') && *(token->value) != ASSIGN)
			token->type = ASSIGN;
		else
			token->type = WORD;
		token = token->next;
	}
	return (0);
}

char	*field_split(char *str)
{
	char	*split;

	split = NULL;
	while(*str)
	{
		if (!is_space(*str))
		{
			split =ft_append_char(split, *str);
			if (is_space(*(str + 1)))
			split = ft_append_char(split, WSPACE);
		}
		str++;
	}
	//free
	return (split);
}

int	param_expansion()
{
	t_token	*token;
	char	*exp_env;

	token = &g_data.tokens;
	while(token)
	{
		if (token->type == TOKEN && *(token->value) == DOLLAR)
		{
			exp_env = getenv(token->value + 1);
			if (token->split == true && exp_env != NULL)
			{
				//free token->value
				token->value = field_split(exp_env);
			}
			else
				token->value = exp_env;
		}
		if (token->type == TOKEN && ft_strchr(token->value, PLACE_HOLDER))
			*(ft_strchr(token->value, PLACE_HOLDER))= DOLLAR;
		token = token->next;
	}
	return (0);
}

int	lex(char *line)
{
	// char	*stripped;
	t_token *temp;

	g_data.state = 0;	
	while (!quotes_matched(line))
		line = ft_strjoin(line, readline("> "));
	printf("line: %s\n", line);
	tokenize(line);
	param_expansion();
	// stripped = strip_quotes(line);
	
	// printf("split: \n");
	// tokenize_operators();
	temp = &g_data.tokens;
	while (temp != NULL)
	{
		printf("%d: %s\n", temp->type, temp->value);
		temp = temp->next;
	}
	return (0);
}
