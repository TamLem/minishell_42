/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:09:01 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/10 15:47:49 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*field_split(char *str)
{
	char	*split;

	split = NULL;
	while (*str)
	{
		if (!is_wspace(*str))
		{
			split = ft_append_char(split, *str);
			if (is_wspace(*(str + 1)))
				split = ft_append_char(split, WWSPACE);
		}
		str++;
	}
	return (split);
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
			token->next = next_token->next;
		else
			token = token->next;
	}
}

void	print_tokens(void)
{
	t_token	*temp;

	temp = g_data.tokens;
	while (temp != NULL)
	{
		printf("token\t");
		printf("%d: %s\n", temp->type, temp->value);
		temp = temp->next;
	}
}

char	*ft_strjoin_withnull(char *s1, char *s2)
{
	char	*ret;
	char	*cp_ret;
	char	*cp_s;

	if (s2 == NULL)
		return (s1);
	if (s1 == NULL)
		return (s2);
	ret = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (NULL);
	cp_ret = ret;
	cp_s = s1;
	while (*cp_s)
		*cp_ret++ = *cp_s++;
	cp_s = s2;
	while (*cp_s)
		*cp_ret++ = *cp_s++;
	*cp_ret = '\0';
	return (ret);
}

bool	is_io_modifier(int type)
{
	if (type == LESS || type == DLESS
		|| type == GREAT || type == DGREAT)
		return (true);
	return (false);
}
