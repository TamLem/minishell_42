/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 21:26:47 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/01 21:08:44 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int	get_state(char pos);

bool	is_WSPACE(char c)
{
	if (c == WWSPACE || c == WTAB || c == WNEWLINE)
		return (true);
	return (false);
}

bool	is_operator(char c)
{
	if (c == LESS || c == GREAT || c == PIPE)
		return (true);
	return (false);
}

bool	shall_split(char *line, char *appended, int state)
{
	char	next;

	next = *(line + 1);

	if (next == '\0')
		return (true);
	if (next == DOLLAR && state != QUOTE)
		return (true);
	if (*appended == DOLLAR && 
		!((ft_isdigit(next) && ft_strlen(appended) > 1)
			|| ft_isalpha(next) || next == '_' || next == QMARK))
		return (true);
	if (is_WSPACE(next) && state == 0)
		return (true);
	if (!is_operator(*line) && is_operator(next) && state == 0)
		return (true);
	if (is_operator(*line) && !is_operator(next) && state == 0)
		return (true);
	if ((is_operator(*line) && (*line != *appended || ft_strlen(appended) > 1)) && state == 0)
		return (true);
	else
		return (false);
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

int	quotes_matched(char *line)
{
	g_data.state = 0;
	while (*line)
	{
		get_state(*line);
		line++;
	}
	if (get_state(*line) == 0)
		return (true);
	else
		return (false);
}
