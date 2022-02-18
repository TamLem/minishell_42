/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:26:02 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/18 15:53:48 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../include/minishell.h"

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

// int	del_token()
// {
// 	t_token	*token;
// 	t_token	*temp;

// 	token = &g_data.tokens;
// 	while (token)
// 	{
// 		if (token->next->value == NULL)
// 		{
// 			temp = token->next;
// 		}
// 	}
// }

char	*strip_quotes(char *line)
{
	char	*stripped;
	int		state;
	t_token	*token;
	char	*quoted;

	token = &g_data.tokens;
	g_data.state = 0;
	while(token)
	{
		stripped = NULL;
		quoted = token->value;
		while (quoted && *quoted)
		{
			state = get_state(*quoted);
			if ((*quoted != QUOTE && *quoted != DQUOTE) 
				|| (state != *quoted && state != 0))
				{
					stripped = ft_append_char(stripped, *quoted);

				}
			quoted++;
		}
		token->value = stripped;
		//free quoted;
		token = token->next;
	}
	return (stripped);
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
			if (exp_env == NULL)
			{	
				free(token->value);
				token->value = NULL;
			}
			else if (token->split == true && exp_env != NULL)
			{
				//free token->value
				token->value = field_split(exp_env);
			}
			else
				token->value = exp_env;
		}
		else if (token->type == TOKEN && ft_strchr(token->value, PLACE_HOLDER))
			*(ft_strchr(token->value, PLACE_HOLDER)) = DOLLAR;
		token = token->next;
	}
	return (0);
}

int	tokenize_operators()
{
	t_token *token;

	token = &g_data.tokens;
	while(token)
	{
		if (token && token->value)
		{
			if(ft_strcmp(token->value, "<") == 0)
				token->type = LESS;
			else if(ft_strcmp(token->value, "<<") == 0)
				token->type = DLESS;
			else if(ft_strcmp(token->value, ">") == 0)
				token->type = GREAT;
			else if(ft_strcmp(token->value, ">>") == 0)
				token->type = DGREAT;
			else if(ft_strcmp(token->value, "|") == 0)
				token->type = PIPE;
			else if(ft_strcmp(token->value, "||") == 0)
				token->type = ERROR;
			else if(ft_strchr(token->value, '=') && *(token->value) != ASSIGN)
				token->type = ASSIGN;
			else if (token->type != REDIR)
				token->type = WORD;
			if ((token->type == LESS || token->type == DLESS 
				|| token->type == GREAT || token->type == DGREAT) && token->next)
					token->next->type = REDIR;	
		}
		token = token->next;
	}
	return (0);
}

int	lex(char *input)
{
	// char	*stripped;
	t_token *temp;
	char	*line;

	line = ft_strdup(input);
	g_data.state = 0;	
	while (!quotes_matched(line))
		line = ft_strjoin(line, ft_strdup(readline("> ")));
	printf("line: %s\n", line);
	tokenize(line);
	param_expansion();
	line = strip_quotes(line);
	// printf("split: \n");
	tokenize_operators();
	temp = &g_data.tokens;
	// while (temp != NULL)
	// {
	// 	printf("token\t");
	// 	printf("%d: %s\n", temp->type, temp->value);
	// 	temp = temp->next;
	// }
	return (0);
}
