/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:26:02 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/05 15:48:55 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../include/minishell.h"

bool	is_space(char c)
{
	if (c == WSPACE || c == TAB || c == NEWLINE)
		return (true);
	return (false);
}

bool	is_operator(char c)
{
	if (c == LESS || c == GREAT || c == PIPE || c == ASSIGN)
		return (true);
	return (false);
}

bool shall_split(char *line)
{
	if (*(line + 1) == '\0')
		return (true);
	if (is_space(*(line + 1)))
		return (true);
	if (is_operator(*(line + 1)) && !is_operator(*line))
		return (true);
	if (is_operator(*(line)) && !is_operator(*(line + 1)))
		return (true);
	else
		return (false);
}

int	parse_space(char *line)
{
	t_token *token;

	token = &g_data.tokens;
	token->value = NULL;
	while(*line != '\0')
	{
		if (!is_space(*line))
		{
			token->value = ft_append_char(token->value, *line);
			if(shall_split(line))
			{
				if(is_operator(*line))
					token->type = OPERATOR;
				else
					token->type = TOKEN;
				if (*(line + 1) != '\0')
					token->next = malloc(sizeof(t_token));
				token = token->next;
				if (token == NULL)
					return (2);
			}
		}
		line++;
	}
	token = NULL;
	return (0);
}

int	lex(char *line)
{
	// printf("line: %s\n", line);
	parse_space(line);

	t_token *temp;

	temp = &g_data.tokens;
	while (temp != NULL)
	{
		printf("%d: %s\n", temp->type, temp->value);
		temp = temp->next;
	}
	return (0);
}
