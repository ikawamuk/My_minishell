/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 23:24:19 by ikawamuk          #+#    #+#             */
/*   Updated: 2025/09/30 22:45:34 by ikawamuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "define.h"
#include "shell.h"
#include "token.h"
#include "parse_utils.h"
#include "libft.h"

int			expand_string(char *str, char **result_p, t_shell *shell);
int			expand_var(char *str, size_t *ip, char **result_p, t_shell *shell);
static int	skip_quote_marker(char *str, size_t *ip, char **result_p);
int			error_expand_string(char **result_p);

int	expand_token_list(t_token_list *list, t_shell *shell)
{
	char	*expanded_word;

	while (list)
	{
		expanded_word = NULL;
		if (expand_string(list->data.word, &expanded_word, shell) != NO_ERROR)
			return (FATAL_ERROR);
		free(list->data.word);
		list->data.word = expanded_word;
		list = list->next;
	}
	return (NO_ERROR);
}

int	expand_string(char *str, char **result_p, t_shell *shell)
{
	size_t	i;

	*result_p = ft_strdup("");
	if (!result_p)
		return (FATAL_ERROR);
	i = 0;
	while (str[i])
	{
		if (is_env_var(str + i))
		{
			if (expand_var(str, &i, result_p, shell) != NO_ERROR)
				return (error_expand_string(result_p));
		}
		else if (str[i] == S_QUOTE_MARKER)
		{
			if (skip_quote_marker(str, &i, result_p) != NO_ERROR)
				return (error_expand_string(result_p));
		}
		else
			if (append_char(result_p, str[i++]) != NO_ERROR)
				return (error_expand_string(result_p));
	}
	return (NO_ERROR);
}

static int	skip_quote_marker(char *str, size_t *ip, char **result_p)
{
	char	quote;

	quote = str[(*ip)];
	if (append_char(result_p, str[(*ip)++]) != NO_ERROR)
		return (error_expand_string(result_p));
	while (str[*ip] && quote != str[*ip])
		if (append_char(result_p, str[(*ip)++]) != NO_ERROR)
			return (error_expand_string(result_p));
	if (append_char(result_p, str[(*ip)++]) != NO_ERROR)
		return (error_expand_string(result_p));
	return (NO_ERROR);
}

int	error_expand_string(char **result_p)
{
	free(*result_p);
	*result_p = NULL;
	return (FATAL_ERROR);
}
