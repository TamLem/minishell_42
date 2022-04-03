/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_param_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:06:53 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/10 15:40:17 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

static int	paramlen(char *param)
{
	int	len;

	len = 0;
	if (param[len] == QMARK)
		return (1);
	if (param[len] != '_' && !ft_isalpha(param[len]))
		return (0);
	while (param[len] == '_' || ft_isalnum(param[len]))
		len++;
	return (len);
}

char	*expand_single(char *init_token, int var_pos, char *var, bool split)
{
	char	*before;
	char	*before_mid;
	char	*after;
	char	*temp;
	int		len;

	len = paramlen(var + 1);
	var = ft_substr(var, 1, len);
	if (*var == QMARK)
		temp = ft_itoa(g_data.exit_status);
	else
		temp = ft_strdup(ft_getenv(var));
	if (temp && split)
		temp = field_split(temp);
	var = temp;
	before = ft_substr(init_token, 0, var_pos);
	after = ft_substr(init_token, var_pos + len + 1, ft_strlen(init_token));
	before_mid = ft_strjoin_withnull(before, var);
	var = ft_strjoin_withnull(before_mid, after);
	return (var);
}

static void	replace_placeholders(void)
{
	t_token	*token;

	token = g_data.tokens;
	while (token)
	{
		if (token->type == TOKEN && ft_strchr(token->value, PLACE_HOLDER))
			*(ft_strchr(token->value, PLACE_HOLDER)) = DOLLAR;
		if (!ft_strchr(token->value, PLACE_HOLDER))
			token = token->next;
	}
}

int	param_expand(void)
{
	t_token	*token;
	char	*exp;
	char	*var;
	int		var_pos;

	token = g_data.tokens;
	while (token)
	{
		var = ft_strchr(token->value, DOLLAR);
		var_pos = ft_strchr_pos(token->value, DOLLAR);
		if (var && (paramlen(var + 1) != 0 || *(var + 1) == QMARK))
		{
			exp = expand_single(token->value, var_pos, var, token->split);
			token->value = exp;
		}
		if (!ft_strchr(token->value, DOLLAR)
			|| paramlen(ft_strchr(token->value, DOLLAR) + 1) == 0)
			token = token->next;
	}
	replace_placeholders();
	return (0);
}
